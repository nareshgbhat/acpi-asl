/*
 * acpi.h: ACPI table headers, defines, etc.
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

#ifndef ACPI_H_
#define ACPI_H_

#define ACPI_NAME_SIZE		4
#define ACPI_OEM_ID_SIZE	6
#define ACPI_OEM_TABLE_ID_SIZE	8

#pragma pack(1)

/* Generic ACPI table header */

struct acpi_table_header {
	char signature[ACPI_NAME_SIZE];	/* ASCII table signature */
	uint32_t length;		/* Length of table in bytes, including this header */
	uint8_t revision;		/* ACPI Specification minor version number */
	uint8_t checksum;		/* To make sum of entire table == 0 */
	char oem_id[ACPI_OEM_ID_SIZE];	/* ASCII OEM identification */
	char oem_table_id[ACPI_OEM_TABLE_ID_SIZE];	/* ASCII OEM table identification */
	uint32_t oem_revision;	/* OEM revision number */
	char asl_compiler_id[ACPI_NAME_SIZE];	/* ASCII ASL compiler vendor ID */
	uint32_t asl_compiler_revision;	/* ASL compiler version */
};

/* HEST - Hardware Error Source Table */

struct acpi_table_hest {
	struct acpi_table_header header;	/* Common ACPI table header */
	uint32_t error_source_count;
};

/* HEST subtable header */

struct acpi_hest_header {
	uint16_t type;
	uint16_t source_id;
};

/* Values for Type field above for subtables */

enum acpi_hest_types {
	ACPI_HEST_TYPE_IA32_CHECK = 0,
	ACPI_HEST_TYPE_IA32_CORRECTED_CHECK = 1,
	ACPI_HEST_TYPE_IA32_NMI = 2,
	ACPI_HEST_TYPE_NOT_USED3 = 3,
	ACPI_HEST_TYPE_NOT_USED4 = 4,
	ACPI_HEST_TYPE_NOT_USED5 = 5,
	ACPI_HEST_TYPE_AER_ROOT_PORT = 6,
	ACPI_HEST_TYPE_AER_ENDPOINT = 7,
	ACPI_HEST_TYPE_AER_BRIDGE = 8,
	ACPI_HEST_TYPE_GENERIC_ERROR = 9,
	ACPI_HEST_TYPE_RESERVED = 10	/* 10 and greater are reserved */
};

/* GAS - Generic Address Structure */
struct acpi_generic_address {
	uint8_t space_id;		/* Address space where struct or register exists */
	uint8_t bit_width;		/* Size in bits of given register */
	uint8_t bit_offset;		/* Bit offset within the register */
	uint8_t access_width;		/* Minimum Access size (ACPI 3.0) */
	uint64_t address;		/* 64-bit address of struct or register */
} __attribute__ ((packed));

/* Hardware Error Notification */

struct acpi_hest_notify {
	uint8_t type;
	uint8_t length;
	uint16_t config_write_enable;
	uint32_t poll_interval;
	uint32_t vector;
	uint32_t polling_threshold_value;
	uint32_t polling_threshold_window;
	uint32_t error_threshold_value;
	uint32_t error_threshold_window;
};

/* 9: Generic Hardware Error Source */

struct acpi_hest_generic {
	struct acpi_hest_header header;
	uint16_t related_source_id;
	uint8_t reserved;
	uint8_t enabled;
	uint32_t records_to_preallocate;
	uint32_t max_sections_per_record;
	uint32_t max_raw_data_length;
	struct acpi_generic_address error_status_address;
	struct acpi_hest_notify notify;
	uint32_t error_block_length;
};

enum {
	CPER_SEV_RECOVERABLE,
	CPER_SEV_FATAL,
	CPER_SEV_CORRECTED,
	CPER_SEV_INFORMATIONAL,
};

/* Generic Error Status block */

#define GHES_ERR_TYPE_UNCORRECTABLE		0
#define GHES_ERR_TYPE_CORRECTABLE		1
#define GHES_ERR_TYPE_MULTIPLE_UNCORRECTABLE	2
#define GHES_ERR_TYPE_MULTIPLE_CORRECTABLE	3

struct acpi_hest_generic_status {
	uint32_t block_status;
	uint32_t raw_data_offset;
	uint32_t raw_data_length;
	uint32_t data_length;
	uint32_t error_severity;
};

/* Generic Error Data entry */

struct acpi_hest_generic_data {
	uint8_t section_type[16];
	uint32_t error_severity;
	uint16_t revision;
	uint8_t validation_bits;
	uint8_t flags;
	uint32_t error_data_length;
	uint8_t fru_id[16];
	uint8_t fru_text[20];
};

typedef struct {
	uint8_t b[16];
} uuid_le;

#define UUID_LE(a, b, c, d0, d1, d2, d3, d4, d5, d6, d7)		\
((uuid_le)								\
{{ (a) & 0xff, ((a) >> 8) & 0xff, ((a) >> 16) & 0xff, ((a) >> 24) & 0xff, \
   (b) & 0xff, ((b) >> 8) & 0xff,					\
   (c) & 0xff, ((c) >> 8) & 0xff,					\
   (d0), (d1), (d2), (d3), (d4), (d5), (d6), (d7) }})

/* Platform Memory */
#define CPER_SEC_PLATFORM_MEM						\
	UUID_LE(0xA5BC1114, 0x6F64, 0x4EDE, 0xB8, 0x63, 0x3E, 0x83,	\
		0xED, 0x7C, 0x83, 0xB1)

#define CPER_MEM_VALID_ERROR_STATUS		0x0001
#define CPER_MEM_VALID_PHYSICAL_ADDRESS		0x0002
#define CPER_MEM_VALID_PHYSICAL_ADDRESS_MASK	0x0004
#define CPER_MEM_VALID_NODE			0x0008
#define CPER_MEM_VALID_CARD			0x0010
#define CPER_MEM_VALID_MODULE			0x0020
#define CPER_MEM_VALID_BANK			0x0040
#define CPER_MEM_VALID_DEVICE			0x0080
#define CPER_MEM_VALID_ROW			0x0100
#define CPER_MEM_VALID_COLUMN			0x0200
#define CPER_MEM_VALID_BIT_POSITION		0x0400
#define CPER_MEM_VALID_REQUESTOR_ID		0x0800
#define CPER_MEM_VALID_RESPONDER_ID		0x1000
#define CPER_MEM_VALID_TARGET_ID		0x2000
#define CPER_MEM_VALID_ERROR_TYPE		0x4000

#define ACPI_ADR_SPACE_SYSTEM_MEMORY		0

/* Memory Error Section */
struct cper_sec_mem_err {
	uint64_t	validation_bits;
	uint64_t	error_status;
	uint64_t	physical_addr;
	uint64_t	physical_addr_mask;
	uint16_t	node;
	uint16_t	card;
	uint16_t	module;
	uint16_t	bank;
	uint16_t	device;
	uint16_t	row;
	uint16_t	column;
	uint16_t	bit_pos;
	uint64_t	requestor_id;
	uint64_t	responder_id;
	uint64_t	target_id;
	uint8_t		error_type;
	uint8_t		reserved;
	uint16_t	rank;
	uint16_t	mem_array_handle;	/* card handle in UEFI 2.4 */
	uint16_t	mem_dev_handle;		/* module handle in UEFI 2.4 */
};

/* ERST Error Log Address Range atrributes */
#define ERST_RANGE_RESERVED	0x0001
#define ERST_RANGE_NVRAM	0x0002
#define ERST_RANGE_SLOW		0x0004

/* ERST command status */
#define ERST_STATUS_SUCCESS			0x0
#define ERST_STATUS_NOT_ENOUGH_SPACE		0x1
#define ERST_STATUS_HARDWARE_NOT_AVAILABLE	0x2
#define ERST_STATUS_FAILED			0x3
#define ERST_STATUS_RECORD_STORE_EMPTY		0x4
#define ERST_STATUS_RECORD_NOT_FOUND		0x5

/* Values for Action field above */

enum acpi_erst_actions {
	ACPI_ERST_BEGIN_WRITE = 0,
	ACPI_ERST_BEGIN_READ = 1,
	ACPI_ERST_BEGIN_CLEAR = 2,
	ACPI_ERST_END = 3,
	ACPI_ERST_SET_RECORD_OFFSET = 4,
	ACPI_ERST_EXECUTE_OPERATION = 5,
	ACPI_ERST_CHECK_BUSY_STATUS = 6,
	ACPI_ERST_GET_COMMAND_STATUS = 7,
	ACPI_ERST_GET_RECORD_ID = 8,
	ACPI_ERST_SET_RECORD_ID = 9,
	ACPI_ERST_GET_RECORD_COUNT = 10,
	ACPI_ERST_BEGIN_DUMMY_WRIITE = 11,
	ACPI_ERST_NOT_USED = 12,
	ACPI_ERST_GET_ERROR_RANGE = 13,
	ACPI_ERST_GET_ERROR_LENGTH = 14,
	ACPI_ERST_GET_ERROR_ATTRIBUTES = 15,
	ACPI_ERST_ACTION_RESERVED = 16	/* 16 and greater are reserved */
};

#define ACPI_ERR_TYPE_PROCSR_CORRECTABLE		0
#define ACPI_ERR_TYPE_PROCSR_UNCORRECTABLE		1
#define ACPI_ERR_TYPE_PROCSR_UNCORRECTABLE_FATAL	2
#define ACPI_ERR_TYPE_MEM_CORRECTABLE			3
#define ACPI_ERR_TYPE_MEM_UNCORRECTABLE			4
#define ACPI_ERR_TYPE_MEM_UNCORRECTABLE_FATAL		5
#define ACPI_ERR_TYPE_PCIE_CORRECTABLE			6
#define ACPI_ERR_TYPE_PCIE_UNCORRECTABLE		7
#define ACPI_ERR_TYPE_PCIE_UNCORRECTABLE_FATAL		8
#define ACPI_ERR_TYPE_PLATFOTM_CORRECTABLE		9
#define ACPI_ERR_TYPE_PLATFOTM_UNCORRECTABLE		10
#define ACPI_ERR_TYPE_PLATFOTM_UNCORRECTABLE_FATAL	11
#define ACPI_ERR_TYPE_VENDOR_DEFINED			31

#define ACPI_EINJ_TRIGGER_TABLE_OFFSET			0x280

enum acpi_einj_actions {
	ACPI_EINJ_BEGIN_OPERATION = 0,
	ACPI_EINJ_GET_TRIGGER_TABLE = 1,
	ACPI_EINJ_SET_ERROR_TYPE = 2,
	ACPI_EINJ_GET_ERROR_TYPE = 3,
	ACPI_EINJ_END_OPERATION = 4,
	ACPI_EINJ_EXECUTE_OPERATION = 5,
	ACPI_EINJ_CHECK_BUSY_STATUS = 6,
	ACPI_EINJ_GET_COMMAND_STATUS = 7,
	ACPI_EINJ_SET_ERROR_TYPE_WITH_ADDRESS = 8,
	ACPI_EINJ_ACTION_RESERVED = 9,	/* 9 and greater are reserved */
	ACPI_EINJ_TRIGGER_ERROR = 0xFF	/* Except for this value */
};

/* Values for Instruction field above */

enum acpi_einj_instructions {
	ACPI_EINJ_READ_REGISTER = 0,
	ACPI_EINJ_READ_REGISTER_VALUE = 1,
	ACPI_EINJ_WRITE_REGISTER = 2,
	ACPI_EINJ_WRITE_REGISTER_VALUE = 3,
	ACPI_EINJ_NOOP = 4,
	ACPI_EINJ_INSTRUCTION_RESERVED = 5	/* 5 and greater are reserved */
};

/* Command status return values */

enum acpi_einj_command_status {
	ACPI_EINJ_SUCCESS = 0,
	ACPI_EINJ_FAILURE = 1,
	ACPI_EINJ_INVALID_ACCESS = 2,
	ACPI_EINJ_STATUS_RESERVED = 3	/* 3 and greater are reserved */
};

/* EINJ Trigger Error Action Table */

struct acpi_einj_trigger {
	uint32_t header_size;
	uint32_t revision;
	uint32_t table_size;
	uint32_t entry_count;
};

/* Subtable header for WHEA tables (EINJ, ERST, WDAT) */

struct acpi_whea_header {
	uint8_t action;
	uint8_t instruction;
	uint8_t flags;
	uint8_t reserved;
	struct acpi_generic_address register_region;
	uint64_t value;		/* Value used with Read/Write register */
	uint64_t mask;		/* Bitmask required for this register instruction */
};

/* Reset to default packing */
#pragma pack()

#endif /* ACPI_H_ */
