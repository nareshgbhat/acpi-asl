/*
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
 * [DSDT] Description of the armv8 VE Model
 *
 */

DefinitionBlock (
	"dsdt.aml",		// output filename
	"DSDT",			// table signature
	2,			// DSDT compliance revision
	"LINARO",		// OEM ID
	"RTSMVEV8",		// table ID
	0x00000004)		// OEM revision
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
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* type, len, reserved, gic_id */
				/* 0008 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, /* uid, flags */
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
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
				/* 0008 */    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Name (MAT1, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
				/* 0008 */    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
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
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
				/* 0008 */    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Name (MAT1, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
				/* 0008 */    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
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
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
				/* 0008 */    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Name (MAT1, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
				/* 0008 */    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
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
					Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive, , , ) {0x2F}
				})
				Return (RBUF)
			}
		}

		Device (PMU0) {
			Name (_HID, "LINA0007")
			Name (_UID, 0)

			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive, , , ) {92, 93, 94, 95}
				})
				Return (RBUF)
			}
		}
	}
}
