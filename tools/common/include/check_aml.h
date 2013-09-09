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

#ifndef CHECK_AML_H_
#define CHECK_AML_H_

#include <sys/queue.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <ctype.h>
#include <endian.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PASS	1
#define FAIL	0
#define INFO	(-1)

#define MIN_TABLE_LENGTH	36
#define RSDP_LEN_OFFSET		20
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

struct table *check_table_entry(unsigned char *buf);
void check_blob_header(unsigned char *blob);
void check_fadt_relocs(unsigned char *blob, int size, uint64_t paddr);
void check_first_table_is_rsdp(unsigned char *blob);
void check_rsdp(unsigned char *blob);
void check_ref_cnts(void);
void check_relocations(unsigned char *blob, int size, uint64_t paddr);
void check_rsdp_relocs(unsigned char *blob, int size, uint64_t paddr);
void check_table_header(char *name, unsigned char *loc);
void check_xsdt_relocs(unsigned char *blob, int size, uint64_t paddr);
int check_print_summary(void);
void presult(int res, char *topic);
void find_all_tables(unsigned char *blob, int size, int base_addr);
struct known_table_info *find_known_table_info(char *sig);
int verify_checksum(unsigned char *start, int offset, int len);
int verify_revision(unsigned char *r, int min);

#endif /* CHECK_AML_H_ */
