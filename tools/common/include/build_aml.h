/*
 * build_aml.h: helper functions for the tool to Make A Blob of ACPI tables
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

#ifndef COMMON_H_
#define COMMON_H_

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

#define BLOB_HEADER_SIZE	8
#define BLOB_MAGIC		"ACPI"
#define BLOB_MAGIC_SIZE		4
#define MAX_LINE		1024
#define NOT_REQUIRED		0
#define REQUIRED		1
#define SIG_LENGTH		4

LIST_HEAD(table_head, table) thead;
struct table_head *theadp;

struct table {
	char *signature;		/* an ACPI table name/signature */
	char *asl_name;			/* ASL file name */
	char *aml_name;			/* corresponding AML name */
	int file_size;			/* aka table size */
	int offset;			/* location in the blob */
	int len;			/* reported table length */
	uint64_t paddr;			/* where it should live in RAM */
	int ref_cnt;			/* reference count */
	LIST_ENTRY(table) tables;
};

int add_table(unsigned char **blob, char *table_name, int offset, int reqd);
void build_aml(int q, char *dir, char *iasl_cmd, struct table *tp);
struct table *build_table_entry(char *dir, char *buf);
struct table *find_table(char *sig);
int get_file_size(char *fname);
int read_manifest(char *dir, char *fname);
void set_blob_header(unsigned char *blob, int blob_size);
void set_checksum(unsigned char *start, int len, uint8_t *cksum);
void write_blob(char *dir, char *fname, unsigned char *blob, int size);
void write_table(unsigned char *blob, struct table *tp, int offset);
int valid_sig(char *sig);

void fixup_facp(unsigned char *blob, int *offset, unsigned long paddr,
		int facs64);
void fixup_rsdp(unsigned char *blob, unsigned long paddr);
void fixup_xsdt(unsigned char **blob, int *offset, unsigned long paddr);

/* Currently a hack to avoid issues on 4k pages on armv7 */
#define PAGE_SIZE 0x1000

#endif /* COMMON_H_ */
