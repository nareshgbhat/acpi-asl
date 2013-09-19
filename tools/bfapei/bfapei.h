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

/* Register write macro helper */
#define WRITE_LONG(blob, offset, value)	 {	\
	uint64_t *add_ptr;			\
	add_ptr = (uint64_t *) (blob + offset); \
	*add_ptr = value;			\
}

/* ERST generic registers offset */
uint64_t erst_reg_map[] = {
	[ACPI_ERST_CHECK_BUSY_STATUS] 		= 0x130,
	[ACPI_ERST_GET_COMMAND_STATUS] 		= 0x138,
	[ACPI_ERST_GET_ERROR_RANGE] 		= 0x168,
	[ACPI_ERST_GET_ERROR_LENGTH] 		= 0x170,
	[ACPI_ERST_GET_ERROR_ATTRIBUTES] 	= 0x178,
};

#define WRITE_ERST_REG(blob, reg, value)	\
	WRITE_LONG(blob, erst_reg_map[reg], value)

/* EINJ generic registers offset */
uint64_t einj_reg_map[] = {
	[ACPI_EINJ_BEGIN_OPERATION] 		= 0x200,
	[ACPI_EINJ_GET_TRIGGER_TABLE] 		= 0x208,
	[ACPI_EINJ_SET_ERROR_TYPE] 		= 0x210,
	[ACPI_EINJ_GET_ERROR_TYPE] 		= 0x218,
	[ACPI_EINJ_END_OPERATION] 		= 0x220,
	[ACPI_EINJ_EXECUTE_OPERATION] 		= 0x228,
	[ACPI_EINJ_CHECK_BUSY_STATUS] 		= 0x230,
	[ACPI_EINJ_GET_COMMAND_STATUS] 		= 0x238,

};

#define WRITE_EINJ_REG(blob, reg, value)	\
	WRITE_LONG(blob, einj_reg_map[reg], value)

#endif
