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

#include "mab.h"

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


void usage(void)
{
	printf("%s %s\n", PROGNAME, VERSION);
	printf("usage: %s -d <dir> -o <blob> -i <manifest> ", PROGNAME);
	printf("-p <paddr> [-c <iasl-cmd>] [-q]\n");
	printf("\n");
	printf("   -d <dir>      => directory of ASL files\n");
	printf("   -o <blob>     => file name for resulting ACPI blob\n");
	printf("   -i <manifest> => list of AML files needed\n");
	printf("   -c <iasl-cmd> => iasl command to use (default: iasl -l)\n");
	printf("   -p <paddr>    => physical address to relocate to\n");
	printf("   -q            => if given, supress output\n");
}

int get_file_size(char *fname)
{
	struct stat buf;
	int err;

	err = stat(fname, &buf);
	if (err)
		printf("? cannot stat %s (%d)\n", fname, err);
	return (err == 0 ? buf.st_size : 0);
}

int valid_sig(char *sig)
{
	char **p;

	p = known_sigs;
	while (*p != NULL) {
		if (strcmp(*p, sig) == 0)
			return 1;
		p++;
	}
	return 0;
}

struct table *build_table_entry(char *dir, char *buf)
{
	struct table *tmp;
	char sig[MAX_LINE];
	char fname[MAX_LINE];
	int ii, n;
	char *p;

	tmp = (struct table *)malloc(sizeof(struct table));
	if (tmp != NULL) {
		memset(tmp, 0, sizeof(struct table));
		memset(sig, 0, MAX_LINE);
		memset(fname, 0, MAX_LINE);

		/* parse the line */
		n = 0;
		for (ii = 0; ii < strlen(buf); ii++) {
			if (buf[ii] == ':' || isspace(buf[ii]))
				break;
			sig[n++] = buf[ii];
		}
		if (!valid_sig(sig)) {
			free(tmp);
			return NULL;
		}
		while (buf[ii] == ':' || isspace(buf[ii]))
			ii++;
		n = 0;
		for (; ii < strlen(buf); ii++) {
			if (buf[ii] == '\n' || !isascii(buf[ii]))
				break;
			fname[n++] = buf[ii];
		}

		/* fill in the struct */
		tmp->signature = (char *)malloc(strlen(sig) + 1);
		memset(tmp->signature, 0, strlen(sig) + 1);
		memcpy(tmp->signature, sig, strlen(sig));

		n = strlen(fname) + strlen(dir) + 2;
		tmp->asl_name = (char *)malloc(n);
		memset(tmp->asl_name, 0, n);
		strcpy(tmp->asl_name, dir);
		strcat(tmp->asl_name, "/");
		strcat(tmp->asl_name, fname);

		tmp->aml_name = (char *)malloc(n);
		memset(tmp->aml_name, 0, n);
		strcpy(tmp->aml_name, tmp->asl_name);
		p = strrchr(tmp->aml_name, '.');
		if (p)
			strcpy(p, ".aml");

		tmp->file_size = -1;	/* need to build .aml file first */
		tmp->offset = -1;
	}

	return tmp;
}

int read_manifest(char *dir, char *fname)
{
	FILE *fp;
	struct table *p;
	char line[MAX_LINE];
	char *tmp;
	char buf[MAX_LINE];

	memset(buf, 0, MAX_LINE);
	strcpy(buf, dir);
	strcat(buf, "/");
	strcat(buf, fname);
	fp = fopen(buf, "r");
	if (!fp)
		return -ENOENT;

	LIST_INIT(&thead);
	memset(line, 0, MAX_LINE);
	tmp = fgets(line, MAX_LINE, fp);
	while (tmp != NULL) {
		if (strlen(line) > 0 && line[0] != '#' && line[0] != '\n') {
			p = build_table_entry(dir, line);
			if (p)
				LIST_INSERT_HEAD(&thead, p, tables);
		}
		memset(line, 0, MAX_LINE);
		tmp = fgets(line, MAX_LINE, fp);
	}
	fclose(fp);

	return 0;
}

void set_blob_header(unsigned char *blob, int blob_size)
{
	uint32_t *psize;

	/* the resulting blob contents are always little-endian */
	memcpy(blob, BLOB_MAGIC, BLOB_MAGIC_SIZE);

	psize = (uint32_t *)(blob + BLOB_MAGIC_SIZE);
	*psize = (uint32_t)(htobe32(blob_size));

}

struct table *find_table(char *sig)
{
	struct table *np;

	LIST_FOREACH(np, &thead, tables) {
		if (strcmp(np->signature, sig) == 0)
			return np;
	}
	return NULL;
}

void write_table(unsigned char *blob, struct table *tp, int offset)
{
	unsigned char *buf;
	unsigned char *start;
	FILE *fp;

	tp->offset = offset;
	start = (unsigned char *)(blob + BLOB_HEADER_SIZE + offset);
	fp = fopen(tp->aml_name, "r");
	if (fp) {
		fread(start, 1, tp->file_size, fp);
		fclose(fp);
	}
}

void write_blob(char *dir, char *fname, unsigned char *blob, int size)
{
	FILE *fp;
	char newname[MAX_LINE];

	memset(newname, 0, MAX_LINE);
	strcpy(newname, dir);
	strcat(newname, "/");
	strcat(newname, fname);

	fp = fopen(newname, "w+");
	if (fp) {
		fwrite(blob, 1, size, fp);
		fclose(fp);
	} else {
		printf("? could not open the blob file: %s\n", newname);
	}
}

void set_checksum(unsigned char *start, int len, uint8_t *cksum)
{
	uint8_t newsum, oldsum;
	uint8_t *p;

	newsum = 0;
	for (p = (uint8_t *)start; p < (uint8_t *)(start + len); p++)
		newsum += *p;

	oldsum = *cksum;
	newsum = (uint8_t)(newsum - oldsum);

	*cksum = (uint8_t)(0 - newsum);
}

int add_table(unsigned char **blob, char *table_name, int offset, int reqd)
{
	struct table *p;
	int new_offset;
	int adjustment = 0;

	p = find_table(table_name);
	new_offset = offset + p->file_size;

	/*
	 * Handle crossing of page boundaries to prevent problems
	 * on armv7 with small page sizes
	 */
	if ((new_offset / PAGE_SIZE) != (offset / PAGE_SIZE)) {
		adjustment = PAGE_SIZE - (offset % PAGE_SIZE);
		/*
		 * If this is the first page crossing remove the
		 * blob header from calculations
		 */
		if (!(offset / PAGE_SIZE))
			adjustment -= BLOB_HEADER_SIZE;
	}

	*blob = realloc(*blob, offset + adjustment + p->file_size + BLOB_HEADER_SIZE);
	if (p) {
		write_table(*blob, p, offset + adjustment);
	} else {
		if (reqd) {
			printf("? %s table is required\n", table_name);
			return 0;
		}
	}

	/* NB: ACPI table size cannot be zero -- there must be a header */
	return p->file_size + adjustment;
}

void fixup_rsdp(unsigned char *blob, uint64_t paddr)
{
	/* We could use the 32-bit RSDT address but that has
	 * essentially been deprecated.  Instead, use the 64-bit
	 * XSDT address though be sure to use little-endian values.
	 */
	const int RSDP_CHECKSUM_BYTES = 20;
	const int RSDP_CHECKSUM_OFFSET = 8;
	const int RSDT_ADDR_OFFSET = 16;
	const int XSDT_ADDR_OFFSET = 24;

	uint8_t  *pcksum;
	uint32_t *stmp;
	uint64_t *ltmp;
	struct table *rsdpp;
	struct table *p;

	/* NB: there are no safety checks on the find_table()
	 * return value because if we've gotten this far and
	 * the RSDP doesn't exist, something else has gone
	 * seriously wrong far earlier.
	 */
	rsdpp = find_table("rsdp");
	stmp = (uint32_t *)(blob + BLOB_HEADER_SIZE +
			rsdpp->offset + RSDT_ADDR_OFFSET);
	ltmp = (uint64_t *)(blob + BLOB_HEADER_SIZE +
			rsdpp->offset + XSDT_ADDR_OFFSET);

	p = find_table("xsdt");
	if (p)
		*ltmp = p->offset + paddr;
	else
		*ltmp = (uint64_t)0;

	p = find_table("rsdt");
	if (p)
		*stmp = p->offset + paddr;
	else
		*stmp = (uint64_t)0;

	/* always reset the checksum, even if it is seldom used */
	pcksum = (uint8_t *)(blob + BLOB_HEADER_SIZE);
	pcksum = (uint8_t *)(pcksum + rsdpp->offset + RSDP_CHECKSUM_OFFSET);
	set_checksum((unsigned char *)(blob + BLOB_HEADER_SIZE + rsdpp->offset),
			RSDP_CHECKSUM_BYTES, pcksum);
}

void fixup_facp(unsigned char *blob, int *offset, uint64_t paddr)
{
	const int DSDT_ADDR_OFFSET = 40;
	const int FACP_CHECKSUM_OFFSET = 9;
	const int FIRMWARE_CTRL_OFFSET = 36;
	const int X_DSDT_ADDR_OFFSET = 140;
	const int X_FIRMWARE_CTRL_OFFSET = 132;

	struct table *facpp;
	struct table *p;
	uint32_t *stmp;
	uint64_t *ltmp;
	uint8_t  *pcksum;

	facpp = find_table("facp");

	/* add in the DSDT and X_DSDT addresses */
	stmp = (uint32_t *)(blob + BLOB_HEADER_SIZE +
			facpp->offset + DSDT_ADDR_OFFSET);
	ltmp = (uint64_t *)(blob + BLOB_HEADER_SIZE +
			facpp->offset + X_DSDT_ADDR_OFFSET);
	p = find_table("dsdt");
	if (p) {
		*stmp = (uint32_t)p->offset + paddr;
		*ltmp = (uint64_t)p->offset + paddr;
	} else {
		*stmp = (uint32_t)0;
		*ltmp = (uint64_t)0;
		return;
	}

	/* add in the FIRMWARE_CTRL and X_FIRMWARE_CTRL addresses */
	stmp = (uint32_t *)(blob + BLOB_HEADER_SIZE +
			facpp->offset + FIRMWARE_CTRL_OFFSET);
	ltmp = (uint64_t *)(blob + BLOB_HEADER_SIZE +
			facpp->offset + X_FIRMWARE_CTRL_OFFSET);
	p = find_table("facs");
	if (p) {
		*stmp = (uint32_t)p->offset + paddr;
		*ltmp = (uint64_t)p->offset + paddr;
	} else {
		*stmp = (uint32_t)0;
		*ltmp = (uint64_t)0;
		return;
	}

	/* always reset the checksum, even if it is seldom used */
	pcksum = (uint8_t *)(blob + BLOB_HEADER_SIZE);
	pcksum = (uint8_t *)(pcksum + facpp->offset + FACP_CHECKSUM_OFFSET);
	set_checksum((unsigned char *)(blob + BLOB_HEADER_SIZE + facpp->offset),
			facpp->file_size, pcksum);
}

void fixup_xsdt(unsigned char **blob, int *offset, uint64_t paddr)
{
	const int FACP_ADDR_OFFSET = 36;
	const int XSDT_CHECKSUM_OFFSET = 9;
	const int XSDT_HEADER_SIZE = 36;

	struct table *xsdtp;
	struct table *p;
	uint64_t *tmp;
	uint8_t  *pcksum;
	int delta;
	int allowed;

	xsdtp = find_table("xsdt");
	tmp = (uint64_t *)(*blob + BLOB_HEADER_SIZE +
			xsdtp->offset + FACP_ADDR_OFFSET);
	allowed = (xsdtp->file_size - XSDT_HEADER_SIZE) / sizeof(uint64_t);

	/* first table must be FACP (aka FADT) */
	p = find_table("facp");
	if (p)
		*tmp = p->offset + paddr;
	else {
		*tmp = (uint64_t)0;
		return;
	}

	/* any tables not already in use go here */
	allowed--;
	tmp++;
	LIST_FOREACH(p, &thead, tables) {
		if (p->offset < 0) {
			if ((unsigned long long)tmp <
					(unsigned long long)
					(xsdtp + xsdtp->file_size)) {
				delta = add_table(blob, p->signature,
						*offset, NOT_REQUIRED);
				*offset += delta;
				*tmp++ = p->offset + paddr;
				allowed--;
				if (allowed < 1)
					break;
			}
		}
	}

	/* always reset the checksum, even if it is seldom used */
	pcksum = (uint8_t *)(*blob + BLOB_HEADER_SIZE);
	pcksum = (uint8_t *)(pcksum + xsdtp->offset + XSDT_CHECKSUM_OFFSET);
	set_checksum((unsigned char *)(*blob + BLOB_HEADER_SIZE + xsdtp->offset),
			xsdtp->file_size, pcksum);
}

void build_aml(int q, char *dir, char *iasl_cmd, struct table *tp)
{
	char cmd[MAX_LINE];
	struct stat mbuf;
	struct stat sbuf;

	if (!tp)
		return;

	if ((stat(tp->aml_name, &mbuf) == 0) &&
			(stat(tp->asl_name, &sbuf) == 0)) {
		if (mbuf.st_mtime > sbuf.st_mtime)
			return;		/* AML file is newer than ASL file */
	}

	strcpy(cmd, iasl_cmd);
	strcat(cmd, " ");
	strcat(cmd, tp->asl_name);
	if (q)
		strcat(cmd, " >/dev/null 2&1");

	system(cmd);
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

	/* parameter handling */
	manifest_name = NULL;
	homedir = NULL;
	acpi_blob_name = NULL;
	iasl_cmd = NULL;
	quiet = 0;

	while ((opt = getopt(argc, argv, "d:o:i:c:p:q")) != EOF) {
		switch (opt) {
		case 'd':
			homedir = optarg;
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
			printf("relocating blob to 0x%llx\n", paddr);
		}
		paddr += BLOB_HEADER_SIZE;
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

	offset = 0;

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
	fixup_facp(blob, &offset, paddr);

	/* this fixup MUST always be called LAST -- it uses any unused tables */
	fixup_xsdt(&blob, &offset, paddr);

	/* set the final blob size in header */
	set_blob_header(blob, offset);

	/* all done, so write out the blob */
	write_blob(homedir, acpi_blob_name, blob, offset + BLOB_HEADER_SIZE);

	if (!quiet) {
		printf("%s %s\n", PROGNAME, VERSION);
		LIST_FOREACH(np, &thead, tables) {
			if (np->offset < 0) {
				for (jj = 0; jj < SIG_LENGTH; jj++)
					sig[jj] = toupper(np->signature[jj]);
				printf("? no room in XSDT for %s (%4s)\n",
						basename(np->asl_name), sig);
			}
		}
		ii = 0;
		LIST_FOREACH(np, &thead, tables) {
			printf("[%03d] %4s : %s (%d bytes @ 0x%08x)\n", ii,
					np->signature, basename(np->aml_name),
					np->file_size, np->offset);
			ii++;
		}
	}

	return err;
}
