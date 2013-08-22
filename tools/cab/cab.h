#ifndef _CAB_H
#define _CAB_H
/*
 * cab.h: tool to Check A Blob of ACPI tables
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

/* VERSION a.b.c = <ACPI standard>.<functionality changes>.<bug fixes> */
const char VERSION[] = { "5.0~3.1" };
const char PROGNAME[] = { "cab" };

#define PASS	1
#define FAIL	0
#define INFO	(-1)

#define BLOB_HEADER_SIZE	8
#define BLOB_MAGIC		"ACPI"
#define BLOB_MAGIC_SIZE		4
#define MAX_LINE		1024
#define MIN_TABLE_LENGTH	36
#define NOT_REQUIRED		0
#define REQUIRED		1
#define RSDP_LEN_OFFSET		20
#define SIG_LENGTH		4
#define TABLE_LEN_OFFSET	4

#define SIG_APIC	"APIC"
#define SIG_BERT	"BERT"
#define SIG_CPEP	"CPEP"
#define SIG_DSDT	"DSDT"
#define SIG_ECDT	"ECDT"
#define SIG_EINJ	"EINJ"
#define SIG_ERST	"ERST"
#define SIG_FACP	"FACP"
#define SIG_FACS	"FACS"
#define SIG_FPDT	"FPDT"
#define SIG_GTDT	"GTDT"
#define SIG_HEST	"HEST"
#define SIG_MCFG	"MCFG"
#define SIG_MCHI	"MCHI"
#define SIG_MPST	"MPST"
#define SIG_MSCT	"MSCT"
#define SIG_OEM		"OEM"
#define SIG_PCCT	"PCCT"
#define SIG_PMTT	"PMTT"
#define SIG_RASF	"RASF"
#define SIG_RSDP	"RSD PTR"
#define SIG_RSDT	"RSDT"
#define SIG_SLIT	"SLIT"
#define SIG_SPMI	"SPMI"
#define SIG_SRAT	"SRAT"
#define SIG_SSDT	"SSDT"
#define SIG_UEFI	"UEFI"
#define SIG_XSDT	"XSDT"

struct known_table_info {
	char *signature;		/* table signature */
	int  min_revision;		/* minimum allowed revision */
};

struct known_table_info known_info[] = {
	{ SIG_APIC, 3 },
	{ SIG_BERT, 1 },
	{ SIG_CPEP, 1 },
	{ SIG_DSDT, 2 },
	{ SIG_ECDT, 1 },
	{ SIG_EINJ, 1 },
	{ SIG_ERST, 1 },
	{ SIG_FACP, 5 },
	{ SIG_FACS, 5 },
	{ SIG_FPDT, 1 },
	{ SIG_GTDT, 1 },
	{ SIG_HEST, 1 },
	{ SIG_MCFG, 1 },
	{ SIG_MCHI, 1 },
	{ SIG_MPST, 1 },
	{ SIG_MSCT, 1 },
	{ SIG_OEM, 1 },
	{ SIG_PMTT, 1 },
	{ SIG_RASF, 1 },
	{ SIG_RSDP, 2 },
	{ SIG_RSDT, 1 },
	{ SIG_SLIT, 1 },
	{ SIG_SPMI, 1 },
	{ SIG_SRAT, 3 },
	{ SIG_SSDT, 2 },
	{ SIG_UEFI, 1 },
	{ SIG_XSDT, 1 },
	{ NULL, 0 }
};

char *known_sigs[] = {
	"APIC",
	"BERT",
	"CPEP",
	"DSDT",
	"ECDT",
	"EINJ",
	"ERST",
	"FACP",
	"FACS",
	"FPDT",
	"GTDT",
	"HEST",
	"MCFG",
	"MCHI",
	"MPST",
	"MSCT",
	"OEM",
	"PCCT",
	"PMTT",
	"RASF",
	"RSD PTR",
	"SLIT",
	"SPMI",
	"SRAT",
	"SSDT",
	"UEFI",
	"XSDT",
	NULL
};

LIST_HEAD(table_head, table) thead;
struct table_head *theadp;

struct table {
	char *signature;		/* an ACPI table name/signature */
	int len;			/* reported table length */
	int offset;			/* location in the blob */
	uint64_t paddr;			/* where it should live in RAM */
	int ref_cnt;			/* reference count */
	LIST_ENTRY(table) tables;
};


struct table *build_table_entry(unsigned char *buf);
void check_blob_header(unsigned char *blob);
void check_fadt_relocs(unsigned char *blob, int size, uint64_t paddr);
void check_first_table_is_rsdp(unsigned char *blob);
void check_rsdp(unsigned char *blob);
void check_ref_cnts(void);
void check_relocations(unsigned char *blob, int size, uint64_t paddr);
void check_rsdp_relocs(unsigned char *blob, int size, uint64_t paddr);
void check_table_header(char *name, unsigned char *loc);
void check_xsdt_relocs(unsigned char *blob, int size, uint64_t paddr);
void find_all_tables(unsigned char *blob, int size, int base_addr);
struct known_table_info *find_known_table_info(char *sig);
struct table *find_table(char *sig);
int get_file_size(char *fname);
void usage(void);
int valid_sig(char *sig);
int verify_checksum(unsigned char *start, int offset, int len);
int verify_revision(unsigned char *r, int min);
void presult(int res, char *topic);

#endif
