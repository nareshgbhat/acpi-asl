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

/* VERSION a.b.c = <public release>.<functionality changes>.<bug fixes> */
const char VERSION[] = { "0.1.0" };
const char PROGNAME[] = { "bfapei" };

#define ACPI_NAME_SIZE		4
#define ACPI_OEM_ID_SIZE	6
#define ACPI_OEM_TABLE_ID_SIZE	8

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
	GHES_SEV_NO = 0x0,
	GHES_SEV_CORRECTED = 0x1,
	GHES_SEV_RECOVERABLE = 0x2,
	GHES_SEV_PANIC = 0x3,
};

/* Generic Error Status block */

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
	uint8_t	error_type;
} __attribute__ ((packed));

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

#define MAX_LINE	1024
#define BFAPEI_OK	0
#define BFAPEI_FAIL	1

#define SIZE	sizeof(uint64_t) + sizeof(struct acpi_hest_generic_status) + \
		sizeof(struct acpi_hest_generic_data) + \
		sizeof (struct cper_sec_mem_err)

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
