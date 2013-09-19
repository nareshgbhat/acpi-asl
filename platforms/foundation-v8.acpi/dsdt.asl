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
	0x00000003)             // OEM revision
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
	}
}
