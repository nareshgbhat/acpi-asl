/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
 *
 * [DSDT] Description of the ARMv8 foundation model
 *
 * This source is released under the terms of the GPLv2.
 */

DefinitionBlock (
	"dsdt.aml",             // output filename
	"DSDT",                 // table signature
	2,                      // DSDT compliance revision
	"LINARO",               // OEM ID
	"FOUNDATI",             // table ID
	0x00000004)             // OEM revision
{
	Scope (\_SB)
	{
		Method (_OSC, 4, NotSerialized)
		{
			/* Platform-Wide OSPM Capabilities */
			If(LEqual(Arg0,ToUUID("0811B06E-4A27-44F9-8D60-3CBBC22E7B48")))
			{
				/* APEI support unconditionally */
				Return (Arg3)
			} Else {
				CreateDWordField (Arg3, Zero, CDW1)
				/* Set invalid UUID error bit */
				Or (CDW1, 0x04, CDW1)
				Return (Arg3)
			}
		}

		Device (HED)
		{
			Name (_HID, EisaId ("PNP0C33"))
			Name (_UID, 0x00)
		}

		Device (SCK0)
		{
			Name (_HID, "ACPI0004")
			Name (_UID, 0x00)
			Method (_STA, 0, NotSerialized)
			{
				Return (0x0F)
			}

			Device (PRC0)
			{
				Name (_HID, "ACPI0007")
				Name (_UID, 0x00)

				/* CPU0 will be always present */
				Method (_STA, 0, NotSerialized)
				{
					Return (0x0F)
				}

				Name (MAT0, Buffer (0x28)
				{
				/* Be careful, little-endian here */
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* type, len, reserved, gic_id */
				/* 0008 */    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, /* uid, flags */
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* parking_version, performance_interrupt */
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* parked_address */
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  /* base_address */
				})

				Name (MAT1, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0008 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Method (_MAT, 0, NotSerialized)
				{
					If (_STA())
					{
						Return (MAT0)
					}
					Else
					{
						Return (MAT1)
					}
				}
			}

			Device (PRC1)
			{
				Name (_HID, "ACPI0007")
				Name (_UID, 0x01)

				Name (STA1, 0x0F)
				Method (_STA, 0, NotSerialized)
				{
					Return (STA1)
				}

				Method (_EJ0, 1, NotSerialized)
				{
					If (LEqual (STA1, 0x0F))
					{
						Store (0x00, STA1)
					}
				}

				Name (MAT0, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
				/* 0008 */    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Name (MAT1, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
				/* 0008 */    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Method (_MAT, 0, NotSerialized)
				{
					If (_STA())
					{
						Return (MAT0)
					}
					Else
					{
						Return (MAT1)
					}
				}
			}

			Device (PRC2)
			{
				Name (_HID, "ACPI0007")
				Name (_UID, 0x02)

				Name (STA2, 0x0F)
				Method (_STA, 0, NotSerialized)
				{
					Return (STA2)
				}

				Method (_EJ0, 1, NotSerialized)
				{
					If (LEqual (STA2, 0x0F))
					{
						Store (0x00, STA2)
					}
				}

				Name (MAT0, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
				/* 0008 */    0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Name (MAT1, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
				/* 0008 */    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Method (_MAT, 0, NotSerialized)
				{
					If (_STA())
					{
						Return (MAT0)
					}
					Else
					{
						Return (MAT1)
					}
				}
			}

			Device (PRC3)
			{
				Name (_HID, "ACPI0007")
				Name (_UID, 0x03)

				Name (STA3, 0x0F)
				Method (_STA, 0, NotSerialized)
				{
					Return (STA3)
				}

				Method (_EJ0, 1, NotSerialized)
				{
					If (LEqual (STA3, 0x0F))
					{
						Store (0x00, STA3)
					}
				}

				Name (MAT0, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
				/* 0008 */    0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Name (MAT1, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
				/* 0008 */    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Method (_MAT, 0, NotSerialized)
				{
					If (_STA())
					{
						Return (MAT0)
					}
					Else
					{
						Return (MAT1)
					}
				}
			}
		}

		Device (PMU0) {
			Name (_HID, "LINA0007")
			Name (_UID, 0)

			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Interrupt (ResourceConsumer, Edge, ActiveBoth, Exclusive, , , ) {92, 93, 94, 95}
				})
				Return (RBUF)
			}
		}

		Device (SMB) {
			Name (_HID, "ACPI0004")
			Name (_UID, 0)

			Name (_CRS, ResourceTemplate () {

			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
			0x00000000,         // Address Space Granularity
			0x08000000,         // Address Range Minimum   (base address in FDT)
			0x0BFFFFFF,         // Address Range Maximum   (base + (len-1))
			0x00000000,         // Address Translation Offset
			0x04000000,         // Address Length           (len in FDT)
			,, , AddressRangeMemory, TypeStatic)

			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
			0x00000000,         // Address Space Granularity
			0x14000000,         // Address Range Minimum   (base address in FDT)
			0x17FFFFFF,         // Address Range Maximum   (base + (len-1))
			0x00000000,         // Address Translation Offset
			0x04000000,         // Address Length           (len in FDT)
			,, , AddressRangeMemory, TypeStatic)

			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
			0x00000000,         // Address Space Granularity
			0x18000000,         // Address Range Minimum   (base address in FDT)
			0x1BFFFFFF,         // Address Range Maximum   (base + (len-1))
			0x00000000,         // Address Translation Offset
			0x04000000,         // Address Length           (len in FDT)
			,, , AddressRangeMemory, TypeStatic)

			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
			0x00000000,         // Address Space Granularity
			0x1C000000,         // Address Range Minimum   (base address in FDT)
			0x1FFFFFFF,         // Address Range Maximum   (base + (len -1))
			0x00000000,         // Address Translation Offset
			0x04000000,         // Address Length           (len in FDT)
			,, , AddressRangeMemory, TypeStatic)

			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
			0x00000000,         // Address Space Granularity
			0x0C000000,         // Address Range Minimum   (base address in FDT)
			0x0FFFFFFF,         // Address Range Maximum   (base + (len-1))
			0x00000000,         // Address Translation Offset
			0x04000000,         // Address Length           (len in FDT)
			,, , AddressRangeMemory, TypeStatic)

			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
			0x00000000,         // Address Space Granularity
			0x10000000,         // Address Range Minimum   (base address in FDT)
			0x13FFFFFF,         // Address Range Maximum   (base + (len-1))
			0x00000000,         // Address Translation Offset
			0x04000000,         // Address Length           (len in FDT)
			,, , AddressRangeMemory, TypeStatic)

			})

		Device (NET0) {
			Name (_HID, "LINA0003")
			Name (_UID, 0)

			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Memory32Fixed (ReadWrite, 0x1a000000, 0x00010000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth, Exclusive, , , ) {0x2F}
				})
				Return (RBUF)
			}
		}

		Device (CLK0) {
			Name (_HID, "LINA0008")
			Name (_UID, 0)

			Method (FREQ, 0x0, NotSerialized) {
				Return (24000000)
			}
		}

		Device (CLK1) {
			Name (_HID, "LINA0008")
			Name (_UID, 1)

			Method (FREQ, 0x0, NotSerialized) {
				Return (1000000)
			}
		}

		Device (CLK2) {
			Name (_HID, "LINA0008")
			Name (_UID, 2)

			Method (FREQ, 0x0, NotSerialized) {
				Return (32768)
			}
		}

		Device (FPGA) {
			Name (_HID, "ACPI0004")
			Name (_UID, 0)

			Name (_CRS, ResourceTemplate () {

			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
			0x00000000,         // Address Space Granularity
			0x1C000000,         // Address Range Minimum   (base address in FDT)
			0x1C1FFFFF,         // Address Range Maximum   (base + (len-1))
			0x00000000,         // Address Translation Offset
			0x00200000,         // Address Length           (len in FDT)
			,, , AddressRangeMemory, TypeStatic)
			})

		Device (SREG) {
			Name (_HID, "LINA0009")
			Name (_UID, 0)

			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate() {
					Memory32Fixed (ReadWrite, 0x1c010000, 0x1000)
			})
			Return (RBUF)
			}
		}

		Device (VIRT) {
			Name (_HID, "LINA0005")
			Name (_UID, 0)

			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate() {
					Memory32Fixed (ReadWrite, 0x1c130000, 0x1000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth, Exclusive, , , ) {0x4A}
				})
				Return (RBUF)
			}
		}
	} // End of FPGA
	} // End SMB

	Device (AMBA) {
		Name (_HID, "AMBA0000")
		Name (_UID, 0)

		Device (SER0) {
			Name (_HID, "LINA000A")
			Name (_ADR, 0x1c090000)
                        Name (_UID, 0)

			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate() {
					Memory32Fixed (ReadWrite, 0x1c090000, 0x1000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth, Exclusive, , , ) {0x25}
				})
			Return (RBUF)
			}
		}

		Device (SER1) {
			Name (_HID, "LINA000A")
			Name (_ADR, 0x1c0a0000)
			Name (_UID, 1)

			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate() {
					Memory32Fixed (ReadWrite, 0x1c0a0000, 0x1000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth, Exclusive, , , ) {0x26}
				})
			Return (RBUF)
			}
		}

		Device (SER2) {
			Name (_HID, "LINA000A")
			Name (_ADR, 0x1c0b0000)
			Name (_UID, 2)

			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate() {
					Memory32Fixed (ReadWrite, 0x1c0b0000, 0x1000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth, Exclusive, , , ) {0x27}
				})
			Return (RBUF)
			}
		}

		Device (SER3) {
			Name (_HID, "LINA000A")
			Name (_ADR, 0x1c0c0000)
			Name (_UID, 3)

			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate() {
					Memory32Fixed (ReadWrite, 0x1c0c0000, 0x1000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth, Exclusive, , , ) {0x28}
			})
			Return (RBUF)
			}
		}
	} // End of AMBA
	}
}
