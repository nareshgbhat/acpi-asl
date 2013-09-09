/*
 * mab.c: main program for the tool to Make A Blob of ACPI tables
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the main directory of this
 * archive for more details.
 *
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
 *
 * NB: all values are assumed to be little-endian in the blob.
 *
 */

#include <build_aml.h>

#include "mab.h"

static void usage(void)
{
	printf("%s %s\n", PROGNAME, VERSION);
	printf("usage: %s -d <dir> -o <blob> -i <manifest> ", PROGNAME);
	printf("-p <paddr> [-c <iasl-cmd>] [-q]\n");
	printf("           [-f] [-H]\n");
	printf("\n");
	printf("   -d <dir>      => directory of ASL files\n");
	printf("   -f            => if given, use FADT 32-bit fields\n");
	printf("   -o <blob>     => file name for resulting ACPI blob\n");
	printf("   -i <manifest> => list of AML files needed\n");
	printf("   -c <iasl-cmd> => iasl command to use (default: iasl -l)\n");
	printf("   -p <paddr>    => physical address to relocate to\n");
	printf("   -q            => if given, suppress output\n");
	printf("   -H            => if given, do NOT add a blob header\n");
}

int main(int argc, char *argv[])
{
	int err = 0;
	int ii, jj;
	int offset;
	int delta;
	unsigned char *blob;
	char *manifest_name;
	char *homedir;
	char *acpi_blob_name;
	char *iasl_cmd;
	char *paddr_cmd;
	uint64_t paddr = 0;
	char sig[SIG_LENGTH];
	struct table *np;
	int opt;
	int quiet;
	int facs64;
	int use_blob_header;

	/* parameter handling */
	manifest_name = NULL;
	homedir = NULL;
	acpi_blob_name = NULL;
	iasl_cmd = NULL;
	paddr_cmd = NULL;
	quiet = 0;
	facs64 = 1;
	use_blob_header = 1;

	while ((opt = getopt(argc, argv, "d:fo:i:c:p:qH")) != EOF) {
		switch (opt) {
		case 'd':
			homedir = optarg;
			break;
		case 'f':
			facs64 = 0;
			break;
		case 'o':
			acpi_blob_name = optarg;
			break;
		case 'i':
			manifest_name = optarg;
			break;
		case 'c':
			iasl_cmd = optarg;
			break;
		case 'p':
			paddr_cmd = optarg;
			break;
		case 'q':
			quiet = 1;
			break;
		case 'H':
			use_blob_header = 0;
			break;
		default:
			usage();
			return 1;
		}
	}

	if ((argc > (optind + 1)) ||
			(manifest_name == NULL) ||
			(acpi_blob_name == NULL) ||
			(homedir == NULL)) {
		printf("? missing a parameter value\n");
		usage();
		return 1;
	}
	if (!iasl_cmd)
		iasl_cmd = "iasl -l";

	if (paddr_cmd) {
		errno = 0;
		paddr = strtoull(paddr_cmd, NULL, 0);
		if (errno) {
			printf("invalid physical address given\n");
			return 1;
		} else {
			printf("relocating blob to 0x%llx\n",
			       (long long unsigned int)paddr);
		}
	} else {
		printf("? missing required physical address parameter\n");
		usage();
		return 1;
	}

	/* what tables do we need to do something about? */
	err = read_manifest(homedir, manifest_name);
	if (err) {
		printf("? could not read manifest: %s\n", manifest_name);
		return 1;
	}

	/* build the AML for each of the files */
	LIST_FOREACH(np, &thead, tables) {
		build_aml(quiet, homedir, iasl_cmd, np);
		np->file_size = get_file_size(np->aml_name);
	}

	blob = (unsigned char *)malloc(BLOB_HEADER_SIZE);

	offset = use_blob_header ? BLOB_HEADER_SIZE : 0;

	delta = add_table(&blob, "rsdp", offset, REQUIRED);
	if (!delta)
		return 1;
	offset += delta;

	delta = add_table(&blob, "xsdt", offset, REQUIRED);
	if (!delta)
		return 1;
	offset += delta;

	delta = add_table(&blob, "facp", offset, REQUIRED);
	if (!delta)
		return 1;
	offset += delta;

	delta = add_table(&blob, "dsdt", offset, REQUIRED);
	if (!delta)
		return 1;
	offset += delta;

	delta = add_table(&blob, "facs", offset, REQUIRED);
	if (!delta)
		return 1;
	offset += delta;

	/* patch up all the offsets if needed */
	fixup_rsdp(blob, paddr);
	fixup_facp(blob, &offset, paddr, facs64);

	/* this fixup MUST always be called LAST -- it uses any unused tables */
	fixup_xsdt(&blob, &offset, paddr);

	/* set the final blob size in header */
	if (use_blob_header)
		set_blob_header(blob, offset);

	/* all done, so write out the blob */
	write_blob(homedir, acpi_blob_name, blob, offset);

	/* make sure we had room for all of the tables */
	LIST_FOREACH(np, &thead, tables) {
		if (np->offset < 0) {
			for (jj = 0; jj < SIG_LENGTH; jj++)
				sig[jj] = toupper(np->signature[jj]);
			printf("? no room in XSDT for %s (%4s)\n",
				basename(np->asl_name), sig);
			err = 2;	/* anything non-zero, really... */
		}
	}

	if (!quiet) {
		printf("%s %s\n", PROGNAME, VERSION);
		ii = 0;
		LIST_FOREACH(np, &thead, tables) {
			printf("[%03d] %4s : %s\n", ii,
			       np->signature, basename(np->aml_name));
			printf("      %d bytes @ 0x%016x, reloc @ 0x%016llx\n",
			       np->file_size, np->offset,
			       (long long unsigned int)np->offset + paddr);
			ii++;
		}
	}

	return err;
}
