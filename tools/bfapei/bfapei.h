/*
 * bfapei.h: tool to make a Blob For APEI testing
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

#ifndef _APEI_H
#define _APEI_H

#include <acpi.h>

/* VERSION a.b.c = <public release>.<functionality changes>.<bug fixes> */
const char VERSION[] = { "0.1.1" };
const char PROGNAME[] = { "bfapei" };

#define BFAPEI_OK	0
#define BFAPEI_FAIL	1

#define SIZE	sizeof(uint64_t) + sizeof(struct acpi_hest_generic_status) + \
		sizeof(struct acpi_hest_generic_data) + \
		sizeof (struct cper_sec_mem_err)

/* ERST generic registers offset */
uint64_t erst_reg_map[] = {
	[ACPI_ERST_CHECK_BUSY_STATUS] 		= 0x130,
	[ACPI_ERST_GET_COMMAND_STATUS] 		= 0x138,
	[ACPI_ERST_GET_ERROR_RANGE] 		= 0x168,
	[ACPI_ERST_GET_ERROR_LENGTH] 		= 0x170,
	[ACPI_ERST_GET_ERROR_ATTRIBUTES] 	= 0x178,
};

/* ERST macro helper */
#define WRITE_LONG(blob, offset, value)	 {	\
	uint64_t *add_ptr;			\
	add_ptr = (uint64_t *) (blob + offset); \
	*add_ptr = value;			\
}

#define WRITE_ERST_REG(blob, reg, value)	\
	WRITE_LONG(blob, erst_reg_map[reg], value)

#endif
