/*
 * bfapei.h: tool to make a Blob For APEI testing
 *
 * Copyright (c) 2013, Tomasz Nowicki <tomasz.nowicki@linaro.org>
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
