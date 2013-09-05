/*
 * cab.c: main program for the tool to Check A Blob of ACPI tables
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
#include <check_aml.h>

#include "cab.h"

static void usage(void)
{
	printf("%s %s\n", PROGNAME, VERSION);
	printf("usage: %s -b <blob> -p <paddr> [-q]\n", PROGNAME);
	printf("\n");
	printf("   -b <blob>     => file name of input ACPI blob\n");
	printf("   -p <paddr>    => physical address used in relocation\n");
	printf("   -q            => if given, supress output\n");
}

int main(int argc, char *argv[])
{
	int ii;
	int size;
	int fd;
	unsigned char *blob;
	char *acpi_blob_name;
	char *paddr_cmd;
	uint64_t paddr = 0;
	struct table *np;
	int opt;
	int quiet;
	int failed;

	/* parameter handling */
	acpi_blob_name = NULL;
	paddr_cmd = NULL;
	quiet = 0;
	failed = 0;

	while ((opt = getopt(argc, argv, "b:p:q")) != EOF) {
		switch (opt) {
		case 'b':
			acpi_blob_name = optarg;
			break;
		case 'p':
			paddr_cmd = optarg;
			break;
		case 'q':
			quiet = 1;
			break;
		default:
			usage();
			return 1;
		}
	}

	if (!quiet)
		printf("%s %s\n", PROGNAME, VERSION);

	if ((argc > (optind + 1)) || (acpi_blob_name == NULL)) {
		printf("? missing a parameter value\n");
		usage();
		return 1;
	}
	if (paddr_cmd) {
		errno = 0;
		paddr = strtoull(paddr_cmd, NULL, 0);
		if (errno) {
			printf("invalid physical address given\n");
			return 1;
		} else {
			printf("assume blob was relocated to 0x%llx\n", paddr);
		}
	} else {
		printf("? missing required physical address parameter\n");
		usage();
		return 1;
	}

	size = get_file_size(acpi_blob_name);
	if (!size) {
		printf("? blob cannot be zero length\n");
		exit(1);
	}

	fd = open(acpi_blob_name, O_RDONLY);
	if (fd < 0) {
		perror(PROGNAME);
		exit(1);
	}
	blob = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd , 0);
	if (blob == MAP_FAILED) {
		perror(PROGNAME);
		exit(1);
	}

	LIST_INIT(&thead);

	check_blob_header(blob);
	check_rsdp(blob);

	find_all_tables(blob, size, paddr);
	if (!quiet) {
		printf("found the following tables....\n");
		ii = 0;
		LIST_FOREACH(np, &thead, tables) {
			printf(
			    "[%03d] %4s: %d bytes @ 0x%08x, loads @ 0x%016x\n",
			    ii, np->signature, np->len, np->offset, np->paddr);
			ii++;
		}
	}
	LIST_FOREACH(np, &thead, tables) {
		if ((strncmp(np->signature, SIG_RSDP,
			     strlen(np->signature) != 0)) &&
		    (strncmp(np->signature, SIG_FACS,
			     strlen(np->signature) != 0))) {
			printf("\nchecking header of %s...\n", np->signature);
			check_table_header(np->signature, blob + np->offset);
		}
	}

	check_relocations(blob, size, paddr);

	failed = check_print_summary();

	munmap(blob, size);

	return (failed > 0) ? 1 : 0;
}
