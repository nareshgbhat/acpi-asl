/*
 * bfapei.c: main program for the tool to make a Blob of APEI tables
 *
 * Copyright (c) 2013, Tomasz Nowicki <tomasz.nowicki@linaro.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * NB: This License is also known as the "BSD 2-Clause License".
 *
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
 *      |  place for EINJ    | EINJ driver reference to this region during
 *      |  registers         | error injection.
 *      |                    |
 *      +--------------------+ +0x300
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

static int bfapei_expand_buf(char **buf, int *size, int reqr_size)
{
	if (*size >= reqr_size)
		return BFAPEI_OK;

	*buf = realloc(*buf, reqr_size);
	if (!(*buf)) {
		printf("Error during memory allocation!\n");
		return BFAPEI_FAIL;
	}
	memset(*buf + *size, 0, reqr_size - *size);
	*size = reqr_size;

	return BFAPEI_OK;
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

	if (bfapei_expand_buf(buf, size, reqr_size))
		return BFAPEI_FAIL;

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
	mem_err->validation_bits |= CPER_MEM_VALID_ERROR_TYPE;
	mem_err->error_type = 2;

	mem_err->validation_bits |= CPER_MEM_VALID_PHYSICAL_ADDRESS;
	mem_err->physical_addr = ~0UL;

	mem_err->validation_bits |= CPER_MEM_VALID_CARD | CPER_MEM_VALID_MODULE |
			CPER_MEM_VALID_BANK | CPER_MEM_VALID_ROW |
			CPER_MEM_VALID_COLUMN | CPER_MEM_VALID_BIT_POSITION;
	mem_err->card = 1;
	mem_err->module = 2;
	mem_err->bank = 3;
	mem_err->row = 1;
	mem_err->column = 2;
	mem_err->bit_pos = 5;

	mem_err->validation_bits |= CPER_MEM_VALID_ERROR_STATUS;
	mem_err->error_status = 4 << 8;

	return BFAPEI_OK;
}

static int bfapei_einj(char **buf, int *size, uint64_t paddr)
{
	struct acpi_hest_generic_status *block_ptr;
	struct acpi_einj_trigger *trigger_tab;
	struct acpi_whea_header *trigger_entry;
	int reqr_size = 0x300;
	uint64_t *add_ptr;

	if (bfapei_expand_buf(buf, size, reqr_size))
		return BFAPEI_FAIL;

	/* Available error type: Memory Correctable */
	WRITE_EINJ_REG(*buf, ACPI_EINJ_GET_ERROR_TYPE,
		       1 << ACPI_ERR_TYPE_MEM_CORRECTABLE);

	WRITE_EINJ_REG(*buf, ACPI_EINJ_GET_COMMAND_STATUS, ACPI_EINJ_SUCCESS);
	WRITE_EINJ_REG(*buf, ACPI_EINJ_CHECK_BUSY_STATUS, 1);

	/*
	 * Nothing to do more than just set status flag for previous prepared
	 * ESB (error status block)
	 */
	WRITE_EINJ_REG(*buf, ACPI_EINJ_GET_TRIGGER_TABLE,
		       paddr + ACPI_EINJ_TRIGGER_TABLE_OFFSET);
	trigger_tab = (struct acpi_einj_trigger *)
		(*buf + ACPI_EINJ_TRIGGER_TABLE_OFFSET);
	trigger_tab->header_size = sizeof(struct acpi_einj_trigger);
	trigger_tab->table_size = sizeof(struct acpi_einj_trigger) +
	    sizeof(struct acpi_whea_header);
	trigger_tab->entry_count = 1;

	trigger_entry = (struct acpi_whea_header *) ++trigger_tab;
	trigger_entry->action = ACPI_EINJ_TRIGGER_ERROR;
	trigger_entry->instruction = ACPI_EINJ_WRITE_REGISTER_VALUE;

	trigger_entry->register_region.space_id = ACPI_ADR_SPACE_SYSTEM_MEMORY;
	trigger_entry->register_region.bit_width = 40;
	trigger_entry->register_region.bit_offset = 0;
	trigger_entry->register_region.access_width = 4;

	/* Obtain address of status block field */
	add_ptr = (uint64_t *) *buf;
	block_ptr = (struct acpi_hest_generic_status *) (++add_ptr);
	trigger_entry->register_region.address =
		paddr + ((char *)&(block_ptr->block_status) - *buf);

	trigger_entry->value = 1 << GHES_ERR_TYPE_CORRECTABLE;
	trigger_entry->mask = ~0x0UL;

	return BFAPEI_OK;
}

static int bfapei_erst(char **buf, int *size, uint64_t paddr)
{
	int reqr_size = 0x200;

	if (bfapei_expand_buf(buf, size, reqr_size))
		return BFAPEI_FAIL;

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

	if (strncmp(blob_type, "einj", 4) == 0) {
		if (bfapei_hest(&buf, &size, paddr, 0))
			return BFAPEI_FAIL;

		if (bfapei_einj(&buf, &size, paddr))
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
	write_blob(homedir, apei_blob_name, (unsigned char *)buf, size);

	if (!quiet) {
		printf("%s blob for %s APEI table testing created\n", apei_blob_name, blob_type);
		printf("Physical address: 0x%llx\n", (long long unsigned int)paddr);
	}

	return BFAPEI_OK;
}
