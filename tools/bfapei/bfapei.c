/*
 * bfapei.c: main program for the tool to make a Blob of APEI tables
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the main directory of this
 * archive for more details.
 *
 * Copyright (c) 2013, Tomasz Nowicki <tomasz.nowicki@linaro.org>
 *
 * NB: all values are assumed to be little-endian in the blob.
 *
 */

#include <ctype.h>
#include <endian.h>
#include <errno.h>
#include <libgen.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/queue.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <build_aml.h>
#include <check_aml.h>

#include "bfapei.h"

/*
 * Overview of blob for APEI testing
 *
 *      +--------------------+ 0x0 base address, need to be obtained from HEST.
 *      |                    |
 *      |  place for status  | HEST and BERT reference to this region
 *      |  block error info  | during error servicing.
 *      |                    |
 *      +--------------------+ +0x100
 *      |                    |
 *      |  place for ERST    | ERST driver reference to this region during
 *      |  registers         | persistent error handling.
 *      |                    |
 *      +--------------------+ +0x200
 *      |                    |
 *
 *     ~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *      |                    |
 *      +--------------------+ +0x2000
 *      |                    |
 *      |  buffer for dmesg  | kernel log is dumping here during panic
 *      |  log               | when there is a kernel oops or panic
 *      |                    |
 *      +--------------------+ +0x12000
 */

static void usage(void) {
	printf("%s %s\n", PROGNAME, VERSION);
	printf("usage: %s -d <dir> -o <blob> -i <manifest>\n", PROGNAME);
	printf("-t [hest|bert|erst]\n");
	printf("   -d <dir>      => directory of ASL files\n");
	printf("   -o <blob>     => file name for resulting APEI blob\n");
	printf("   -i <manifest> => list of AML files needed\n");
	printf("   -t            => blob type for APEI\n");
	printf("   -q            => if given, supress output\n");
}

static uint64_t obtain_esb(char *homedir, char *manifest_name)
{
	int err, table_size, i, error_source_count;
	struct acpi_hest_generic *generic;
	struct acpi_table_hest *hest_hdr;
	struct table *p;
	char *blob;
	FILE *fp;

	/* What tables can we handle with */
	err = read_manifest(homedir, manifest_name);
	if (err) {
		printf("? could not read manifest: %s\n", manifest_name);
		return 0;
	}

	/* HEST table would be candidate */
	p = find_table("hest");
	if (!p) {
		printf("Not found hest table!\n");
		return 0;
	}

	if (!p->aml_name) {
		printf("No aml file created for %s table!\n", p->asl_name);
		return 0;
	}

	table_size = get_file_size(p->aml_name);
	blob = (char *)malloc(table_size);
	if (!blob) {
		printf("Memory allocation error!\n");
		return 0;
	}

	fp = fopen(p->aml_name, "r");
	if (!fp) {
		printf("File %s can not be opened!\n", p->aml_name);
		return 0;
	}
	table_size = fread(blob, 1, table_size, fp);
	fclose(fp);

	/* How many error sources we should traverse looking for GHES ? */
	hest_hdr = (struct acpi_table_hest *)blob;
	error_source_count = hest_hdr->error_source_count;

	blob = (char *)(hest_hdr + 1);
	generic = (struct acpi_hest_generic *)blob;
	for (i = 0; i < error_source_count; i++) {
		if (generic->header.type == ACPI_HEST_TYPE_GENERIC_ERROR)
			return generic->error_status_address.address;
	}

	return 0;
}

static int bfapei_hest(char **buf, int *size, uint64_t paddr, int status)
{
	struct acpi_hest_generic_status *block_ptr;
	struct acpi_hest_generic_data *gdata;
	struct cper_sec_mem_err *mem_err;
	uint64_t *add_ptr;
	int reqr_size = sizeof(uint64_t) +
			sizeof(struct acpi_hest_generic_status) +
			sizeof(struct acpi_hest_generic_data) +
			sizeof (struct cper_sec_mem_err);

	if (*size < reqr_size) {
		*buf = realloc(*buf, *size + reqr_size);
		if (!(*buf)) {
			printf("Error during memory allocation!\n");
			return BFAPEI_FAIL;
		}
		memset(*buf + *size, 0, reqr_size - *size);
		*size += reqr_size;
	}

	/*
	 * Fill in blob which will be parsed by GHES driver.
	 */

	/* First point to generic error status block */
	add_ptr = (uint64_t *) *buf;
	*add_ptr = paddr + sizeof(uint64_t);

	/* Fill in generic error status block */
	block_ptr = (struct acpi_hest_generic_status *) (++add_ptr);
	block_ptr->block_status = status;
	block_ptr->data_length = sizeof(struct acpi_hest_generic_data);
	block_ptr->error_severity = GHES_SEV_CORRECTED;

	/* Fill in generic error data entry */
	gdata = (struct acpi_hest_generic_data *) (block_ptr + 1);
	memcpy(gdata->section_type, (void *) &CPER_SEC_PLATFORM_MEM,
			sizeof(uuid_le));
	gdata->error_data_length = sizeof(struct cper_sec_mem_err);
	block_ptr->data_length += gdata->error_data_length;

	mem_err = (struct cper_sec_mem_err *) (gdata + 1);
	/* Place for more specific err info */

	return BFAPEI_OK;
}

static int bfapei_erst(char **buf, int *size, uint64_t paddr)
{
	int reqr_size = 0x400;

	if (*size < reqr_size) {
		*buf = realloc(*buf, *size + reqr_size);
		if (!(*buf)) {
			printf("Error during memory allocation!\n");
			return BFAPEI_FAIL;
		}
		memset(*buf + *size, 0, reqr_size - *size);
		*size += reqr_size;
	}

	/*
	 * Fill in ERST registers.
	 */
	WRITE_ERST_REG(*buf, ACPI_ERST_GET_COMMAND_STATUS, ERST_STATUS_SUCCESS);
	WRITE_ERST_REG(*buf, ACPI_ERST_CHECK_BUSY_STATUS, 1);

	WRITE_ERST_REG(*buf, ACPI_ERST_GET_ERROR_RANGE, paddr + 0x2000);
	WRITE_ERST_REG(*buf, ACPI_ERST_GET_ERROR_LENGTH, 0x10000);
	WRITE_ERST_REG(*buf, ACPI_ERST_GET_ERROR_ATTRIBUTES, ERST_RANGE_SLOW);

	return BFAPEI_OK;
}

int main(int argc, char *argv[]) {
	char *homedir, *apei_blob_name, *manifest_name, *blob_type;
	int opt, size = 0, quiet = 0;
	uint64_t paddr;
	char *buf = NULL;;

	while ((opt = getopt(argc, argv, "d:o:i:t:q")) != EOF) {
		switch (opt) {
		case 'd':
			homedir = optarg;
			break;
		case 'o':
			apei_blob_name = optarg;
			break;
		case 'i':
			manifest_name = optarg;
			break;
		case 't':
			blob_type = optarg;
			break;
		case 'q':
			quiet = 1;
			break;
		default:
			usage();
			return BFAPEI_FAIL;
		}
	}

	if ((argc > (optind + 1)) || (apei_blob_name == NULL) ||
	    (homedir == NULL) || (manifest_name == NULL) ||
	    (blob_type == NULL)) {
		printf("Missing a parameter value\n");
		usage();
		return BFAPEI_FAIL;
	}

	paddr = obtain_esb(homedir, manifest_name);
	if (!paddr) {
		printf("No Error Status Block address obtained !\n");
		return BFAPEI_FAIL;
	}

	if (strncmp(blob_type, "hest", 4) == 0) {
		if (bfapei_hest(&buf, &size, paddr, 0))
			return BFAPEI_FAIL;
	}

	/* Set status flag so error will be visible for BERT driver */
	if (strncmp(blob_type, "bert", 4) == 0) {
		if (bfapei_hest(&buf, &size, paddr, 1))
			return BFAPEI_FAIL;
	}

	if (strncmp(blob_type, "erst", 4) == 0) {
		if (bfapei_erst(&buf, &size, paddr))
			return BFAPEI_FAIL;
	}

	/* Save buffer to specified file. */
	write_blob(homedir, apei_blob_name, buf, size);

	if (!quiet) {
		printf("%s blob for %s APEI table testing created\n", apei_blob_name, blob_type);
		printf("Physical address: 0x%llx\n", paddr);
	}

	return BFAPEI_OK;
}
