#ifndef _MAB_H
#define _MAB_H
/*
 * mab.h: tool to Make A Blob of ACPI tables
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

#include <stdint.h>
#include <string.h>

#include <sys/queue.h>

#define BLOB_HEADER_SIZE	8
#define BLOB_MAGIC		"ACPI"
#define BLOB_MAGIC_SIZE		4
#define MAX_LINE		1024
#define NOT_REQUIRED		0
#define REQUIRED		1
#define SIG_LENGTH		4

const char VERSION[] = { "0.27.2" };
const char PROGNAME[] = { "mab" };

char *known_sigs[] = {
	"apic",
	"bert",
	"cpep",
	"dsdt",
	"ecdt",
	"einj",
	"erst",
	"facp",
	"facs",
	"fpdt",
	"gtdt",
	"hest",
	"mcfg",
	"mchi",
	"mpst",
	"msct",
	"oem",
	"pcct",
	"pmtt",
	"rasf",
	"rsdp",
	"slit",
	"spmi",
	"srat",
	"ssdt",
	"uefi",
	"xsdt",
	NULL
};

LIST_HEAD(table_head, table) thead;
struct table_head *theadp;

struct table {
	char *signature;		/* an ACPI table name/signature */
	char *asl_name;			/* ASL file name */
	char *aml_name;			/* corresponding AML name */
	int file_size;			/* aka table size */
	int offset;			/* location in the blob */
	LIST_ENTRY(table) tables;
};

int add_table(unsigned char *blob, char *table_name, int offset, int reqd);
void build_aml(int q, char *dir, char *iasl_cmd, struct table *tp);
struct table *build_table_entry(char *dir, char *buf);
struct table *find_table(char *sig);
int get_file_size(char *fname);
int read_manifest(char *dir, char *fname);
void set_blob_header(unsigned char *blob, int blob_size);
void set_checksum(unsigned char *start, int len, uint8_t *cksum);
void write_blob(char *dir, char *fname, unsigned char *blob, int size);
void write_table(unsigned char *blob, struct table *tp, int offset);
void usage(void);
int valid_sig(char *sig);

void fixup_facp(unsigned char *blob, int *offset);
void fixup_rsdp(unsigned char *blob);
void fixup_xsdt(unsigned char *blob, int *offset);

#endif
