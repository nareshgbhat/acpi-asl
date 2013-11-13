/*
 * check_aml.c: helper functions for the tool to Check A Blob of ACPI tables
 *
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
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

#include <build_aml.h>
#include <check_aml.h>

int passed;
int failed;

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

struct table *check_table_entry(unsigned char *buf)
{
	struct table *tmp;
	const int RSDP_NUDGE = 3;
	int len;

	tmp = (struct table *)malloc(sizeof(struct table));
	if (tmp != NULL) {
		memset(tmp, 0, sizeof(struct table));

		/* fill in the struct */
		len = SIG_LENGTH + 1;
		if (strncmp((char *)buf, SIG_RSDP, SIG_LENGTH + RSDP_NUDGE) == 0)
			len += RSDP_NUDGE;
		tmp->signature = (char *)malloc(len);
		memset(tmp->signature, 0, len);
		memcpy(tmp->signature, buf, len - 1);

		LIST_INSERT_HEAD(&thead, tmp, tables);
	}

	return tmp;
}

struct known_table_info *find_known_table_info(char *sig)
{
	struct known_table_info *np;

	for (np = known_info; np->signature != NULL; np++) {
		if (strncmp(np->signature, sig, strlen(np->signature)) == 0)
			return np;
	}
	return NULL;
}

int verify_checksum(unsigned char *start, int offset, int len)
{
	uint8_t newsum, oldsum;
	uint8_t *p;
	uint8_t old_cksum, cksum;

	old_cksum = start[offset];
	cksum = old_cksum;
	newsum = 0;
	for (p = (uint8_t *)start; p < (uint8_t *)(start + len); p++)
		newsum += *p;

	oldsum = cksum;
	newsum = (uint8_t)(newsum - oldsum);

	cksum = (uint8_t)(0 - newsum);

	return (old_cksum == cksum ? PASS : FAIL);
}

int verify_revision(unsigned char *r, int min)
{
	return (*(uint8_t *)r >= min ? PASS : FAIL);
}

void check_blob_header(unsigned char *blob)
{
	int res;

	printf("\nchecking blob header...\n");
	res = strncmp((char *)blob, BLOB_MAGIC, BLOB_MAGIC_SIZE);
	res = (res == 0 ? PASS : FAIL);
	presult(res, "blob magic number is correct");
}

void check_table_header(char *name, unsigned char *loc)
{
	const int CHECKSUM_OFFSET = 9;
	const int CREATOR_ID_OFFSET = 28;
	const int CREATOR_REV_OFFSET = 32;
	const int OEMID_OFFSET = 10;
	const int OEMID_LEN = 6;
	const int REVISION_OFFSET = 8;

	struct known_table_info *kp;
	char buf[MAX_LINE];
	int res;
	uint32_t len;

	/* valid signature? */
	kp = find_known_table_info(name);
	res = (kp ? PASS : FAIL);
	memset(buf, 0, MAX_LINE);
	sprintf(buf, "%s: signature is correct", name);
	presult(res, buf);

	if (!kp) {
		printf("? %s is an unknown table\n", name);
		return;
	}

	/* possibly usable length? */
	len = *(uint32_t *)(loc + TABLE_LEN_OFFSET);
	res = PASS;
	if ((len <= 0) || (len < MIN_TABLE_LENGTH))
		res = FAIL;
	memset(buf, 0, MAX_LINE);
	sprintf(buf, "%s: table length is reasonable (%d)", name, len);
	presult(res, buf);

	/* valid checksum? */
	res = verify_checksum(loc, CHECKSUM_OFFSET, len);
	memset(buf, 0, MAX_LINE);
	sprintf(buf, "%s: checksum is correct", name);
	presult(res, buf);

	/* valid revision number? */
	res = verify_revision(loc + REVISION_OFFSET, kp->min_revision);
	memset(buf, 0, MAX_LINE);
	sprintf(buf, "%s: minimum revision is correct", name);
	presult(res, buf);

	/* non-empty OEMID field? */
	res = (loc[OEMID_OFFSET] != 0 ? PASS : FAIL);
	memset(buf, 0, MAX_LINE);
	sprintf(buf, "%s: there is an OEMID (", name);
	strncat(buf, (char *)(loc + OEMID_OFFSET), OEMID_LEN);
	strncat(buf, ")", 1);
	presult(res, buf);

	/* non-empty CreatorID field? */
	res = (loc[CREATOR_ID_OFFSET] != 0 ? PASS : FAIL);
	memset(buf, 0, MAX_LINE);
	sprintf(buf, "%s: there is a CreatorID", name);
	presult(res, buf);

	/* non-empty CreatorRevision field? */
	res = (loc[CREATOR_REV_OFFSET] != 0 ? PASS : FAIL);
	memset(buf, 0, MAX_LINE);
	sprintf(buf, "%s: there is a CreatorRevision", name);
	presult(res, buf);
}

void check_first_table_is_rsdp(unsigned char *blob)
{
	int res;

	res = strncmp((char *)blob + BLOB_HEADER_SIZE, SIG_RSDP, strlen(SIG_RSDP));
	res = (res == 0 ? PASS : FAIL);
	presult(res, "first table has RSDP signature");
}

void check_rsdp(unsigned char *blob)
{
	const int RSDP_FIRST_CKSUM_OFFSET = 8;
	const int RSDP_FIRST_CKSUM_LEN = 20;
	const int RSDP_SECOND_CKSUM_OFFSET = 32;
	const int RSDP_SECOND_CKSUM_LEN = 36;
	const int RSDP_RSDT_ADDR_OFFSET = 16;

	unsigned char *ptr;
	int res;
	uint32_t rsdt_addr;

	ptr = blob + BLOB_HEADER_SIZE;
	printf("\nchecking RSDP...\n");
	check_first_table_is_rsdp(blob);

	res = verify_checksum(ptr, RSDP_FIRST_CKSUM_OFFSET,
			      RSDP_FIRST_CKSUM_LEN);
	presult(res, "first RSDP checksum verified");

	res = verify_checksum(ptr, RSDP_SECOND_CKSUM_OFFSET,
			      RSDP_SECOND_CKSUM_LEN);
	presult(res, "second RSDP checksum verified");

	rsdt_addr = *(uint32_t *)(ptr + RSDP_RSDT_ADDR_OFFSET);
	res = (rsdt_addr == 0) ? PASS : FAIL;
	presult(res, "RSDT address is null");
}

void find_all_tables(unsigned char *blob, int size, int base_addr)
{
	struct table *tp;
	unsigned char *p;
	int offset;
	int delta;

	/* this assumes that all signatures and lengths are correct */
	printf("\nscanning for tables...\n");

	p = blob + BLOB_HEADER_SIZE;
	offset = (int)(p - blob);

	while (offset + SIG_LENGTH < size) {
		if (valid_sig((char *)p)) {
			tp = check_table_entry(p);
			if (tp) {
				delta = TABLE_LEN_OFFSET;
				if (strcmp(tp->signature, SIG_RSDP) == 0)
					delta = RSDP_LEN_OFFSET;
				tp->len = *(uint32_t *)(p + delta);
				tp->offset = offset;
				tp->paddr = base_addr + offset;

				offset += *(uint32_t *)(p + delta);
				p += tp->len;
			} else {
				printf("? no room for building a table\n");
				exit(1);
			}
		} else {
			/* skip forward until we find something; a table
			 * could have been moved to the next page boundary */
			while (offset + SIG_LENGTH < size) {
				p++;
				offset++;
				if (isalpha(*p) && valid_sig((char *)p))
					break;
			}
		}
	}
}

void check_rsdp_relocs(unsigned char *blob, int size, uint64_t paddr)
{
	const int RSDT_ADDR_OFFSET = 16;
	const int XSDT_ADDR_OFFSET = 24;

	struct table *np, *xp;
	int res;
	uint32_t rsdt_addr;
	uint64_t xsdt_addr;

	printf("\nchecking RSDP relocations...\n");

	res = FAIL;
	np = find_table(SIG_RSDP);
	if (np) {
		np->ref_cnt++;

		rsdt_addr = *(uint32_t *)(blob + np->offset + RSDT_ADDR_OFFSET);
		res = (rsdt_addr == 0) ? PASS : FAIL;
		presult(res, "RSDP has null RSDT pointer");

		xsdt_addr = *(uint32_t *)(blob + np->offset + XSDT_ADDR_OFFSET);
		xp = find_table(SIG_XSDT);
		if (xp) {
			xp->ref_cnt++;
			if ((xsdt_addr == xp->paddr) &&
			    (strncmp((char *)blob + xp->offset, SIG_XSDT,
				     strlen(xp->signature)) == 0))
				res = PASS;
		}
		presult(res, "RSDP has correct XSDT pointer");
	} else {
		res = FAIL;
		presult(res, "RSDP has null RSDT pointer");
		presult(res, "RSDP has correct XSDT pointer");
	}
}

void check_xsdt_relocs(unsigned char *blob, int size, uint64_t paddr)
{
	const int XSDT_ENTRY_START = 36;
	const int XSDT_ENTRY_SIZE = 8;

	struct table *np, *xp;
	int res;
	int cnt;
	int ii;
	int offset;
	uint32_t len;
	uint64_t *tpaddr;
	char buf[MAX_LINE];

	printf("\nchecking XSDT relocations...\n");

	res = FAIL;
	np = find_table(SIG_XSDT);
	if (np) {
		len = *(uint32_t *)(blob + np->offset + TABLE_LEN_OFFSET);
		cnt = (len - XSDT_ENTRY_START) / XSDT_ENTRY_SIZE;
		tpaddr = (uint64_t *)(blob + np->offset + XSDT_ENTRY_START);
		if (len < 1) {
			printf("? XSDT can not have an empty list\n");
			exit(1);
		}

		/* first entry needs to be the FACP (aka FADT) */
		offset = (*tpaddr - paddr);
		if (strncmp((char *)blob + offset, SIG_FACP, strlen(SIG_FACP)) == 0)
			res = PASS;
		presult(res, "first XSDT entry points to the FADT (aka FACP)");

		/* verify all the relocations, best we can */
		for (ii = 0; ii < cnt; ii++, tpaddr++) {
			offset = (*tpaddr - paddr);
			res = FAIL;
			if (valid_sig((char *)blob + offset)) {
				xp = find_table((char *)blob + offset);
				if (xp) {
					xp->ref_cnt++;
					if ((*tpaddr == xp->paddr) &&
					    (strncmp((char *)blob + xp->offset,
						    (char *)blob + offset,
						   strlen(xp->signature)) == 0))
						res = PASS;
					memset(buf, 0, MAX_LINE);
					sprintf(buf,
					       "XSDT has correct %s pointer",
					       xp->signature);
					presult(res, buf);
				} else {
					memset(buf, 0, MAX_LINE);
					sprintf(buf,
			       "XSDT entry %d does not point to a valid table",
					       ii);
					presult(res, buf);
				}
			}
		}
	} else {
		printf("? XSDT can not be found in table list\n");
		exit(1);
	}
}

void check_fadt_relocs(unsigned char *blob, int size, uint64_t paddr)
{
	const int FWCTL_OFFSET = 36;
	const int DSDT_OFFSET = 40;
	const int XFWCTL_OFFSET = 132;
	const int XDSDT_OFFSET = 140;

	struct table *np, *xp;
	uint32_t fwctl, dsdt;
	uint64_t xfwctl, xdsdt;
	uint64_t tpaddr;
	int res;
	int offset;

	printf("\nchecking FADT relocations...\n");
	np = find_table(SIG_FACP);
	if (np) {
		fwctl = *(uint32_t *)(blob + np->offset + FWCTL_OFFSET);
		xfwctl = *(uint64_t *)(blob + np->offset + XFWCTL_OFFSET);
		res = FAIL;
		if ((fwctl == 0 && xfwctl == 0) ||	/* no FACS is okay */
		    (fwctl == 0 && xfwctl != 0) ||
		    (fwctl != 0 && xfwctl == 0))
			res = PASS;
		presult(res, "FADT has a proper 32-bit FACS pointer");
		presult(res, "FADT has a proper 64-bit FACS pointer");
		if (fwctl != 0 && xfwctl != 0)
			presult(INFO,
				"both fields have been set, not just one");

		if (fwctl != 0 || xfwctl != 0) {
			tpaddr = (fwctl == 0) ? xfwctl : fwctl;
			offset = tpaddr - paddr;

			xp = find_table(SIG_FACS);
			if (xp) {
				xp->ref_cnt++;
				res = FAIL;
				if ((tpaddr == xp->paddr) &&
				    (strncmp((char *)blob + xp->offset,
					    (char *)blob + offset,
					     strlen(xp->signature)) == 0))
					res = PASS;
				presult(res, "FADT has correct FACS pointer");

			} else {
				printf("? FADT refers to an FACS but ");
				printf("there is no such table\n");
				exit(1);
			}
		}

		dsdt = *(uint32_t *)(blob + np->offset + DSDT_OFFSET);
		xdsdt = *(uint64_t *)(blob + np->offset + XDSDT_OFFSET);
		res = FAIL;
		if ((dsdt == 0 && xdsdt != 0) ||	/* must have a DSDT */
		    (dsdt != 0 && xdsdt == 0))
			res = PASS;
		presult(res, "FADT has a proper 32-bit DSDT pointer");
		presult(res, "FADT has a proper 64-bit DSDT pointer");
		if (dsdt != 0 && xdsdt != 0)
			presult(INFO,
				"both fields have been set, not just one");

		if (dsdt != 0 || xdsdt != 0) {
			tpaddr = (dsdt == 0) ? xdsdt : dsdt;
			offset = tpaddr - paddr;

			xp = find_table(SIG_DSDT);
			if (xp) {
				xp->ref_cnt++;
				res = FAIL;
				if ((tpaddr == xp->paddr) &&
				    (strncmp((char *)blob + xp->offset,
					    (char *)blob + offset,
					     strlen(xp->signature)) == 0))
					res = PASS;
				presult(res, "FADT has correct DSDT pointer");

			} else {
				printf("? FADT refers to a DSDT but ");
				printf("there is no such table\n");
				exit(1);
			}
		}

	} else {
		printf("? FADT (aka FACP) can not be found in table list\n");
		exit(1);
	}
}

void check_ref_cnts(void)
{
	struct table *np;
	int res;
	char buf[MAX_LINE];

	printf("\nchecking references to tables...\n");
	LIST_FOREACH(np, &thead, tables) {
		memset(buf, 0, MAX_LINE);
		sprintf(buf, "%s referenced only once", np->signature);
		res = (np->ref_cnt == 1) ? PASS : FAIL;
		presult(res, buf);
	}

}

void check_relocations(unsigned char *blob, int size, uint64_t paddr)
{
	check_rsdp_relocs(blob, size, paddr);
	check_xsdt_relocs(blob, size, paddr);
	check_fadt_relocs(blob, size, paddr);
	check_ref_cnts();
}

void presult(int res, char *topic)
{
	if (res != 0)
		passed++;
	else
		failed++;
	if (res >= 0)
		printf("[%4s] %s\n", (res != 0) ? "PASS" : "FAIL", topic);
	else
		printf("[%4s] %s\n", "INFO", topic);
}

int check_print_summary(void)
{
	check_print_summary();
	printf("\nTotal tests: %d\n", passed + failed);
	printf("Passed: %d\n", passed);
	printf("Failed: %d\n", failed);
	printf("Success rate: %0.1f%%\n",
	       (100.0 * (float)passed) / (float)(passed + failed));

	return failed;
}
