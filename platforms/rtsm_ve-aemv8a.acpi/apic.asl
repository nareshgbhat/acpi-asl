/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
 *
 * [APIC] Multiple APIC Description Table (MADT)
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 * This source is released under the terms of the GPLv2.
 */

[0004]                          Signature : "APIC"
[0004]                       Table Length : 000000F6
[0001]                           Revision : 03
[0001]                           Checksum : B0
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "RTSMVEV8"
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20110623

[0004]                 Local Apic Address : 2C002000
[0004]              Flags (decoded below) : 00000001
                      PC-AT Compatibility : 0

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000000  /* Should be equal to FDT provided or CPU hardware ID */
[0004]                      Processor UID : 00000000
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]           Parking Protocol Version : 00000000
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 0000000000000000
[0008]                       Base Address : 000000002C002000  /* this is the foundation model's GIC address */

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000001
[0004]                      Processor UID : 00000001
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]           Parking Protocol Version : 00000000
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 0000000000000000
[0008]                       Base Address : 000000002C002000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000002
[0004]                      Processor UID : 00000002
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]           Parking Protocol Version : 00000000
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 0000000000000000
[0008]                       Base Address : 000000002C002000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000003
[0004]                      Processor UID : 00000003
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]           Parking Protocol Version : 00000000
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 0000000000000000
[0008]                       Base Address : 000000002C002000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000004
[0004]                      Processor UID : 00000004
[0004]              Flags (decoded below) : 00000000
                        Processor Enabled : 0
[0004]           Parking Protocol Version : 00000000
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 0000000000000000
[0008]                       Base Address : 000000002C002000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000005
[0004]                      Processor UID : 00000005
[0004]              Flags (decoded below) : 00000000
                        Processor Enabled : 0
[0004]           Parking Protocol Version : 00000000
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 0000000000000000
[0008]                       Base Address : 000000002C002000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000006
[0004]                      Processor UID : 00000006
[0004]              Flags (decoded below) : 00000000
                        Processor Enabled : 0
[0004]           Parking Protocol Version : 00000000
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 0000000000000000
[0008]                       Base Address : 000000002C002000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000007
[0004]                      Processor UID : 00000007
[0004]              Flags (decoded below) : 00000000
                        Processor Enabled : 0
[0004]           Parking Protocol Version : 00000000
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 0000000000000000
[0008]                       Base Address : 000000002C002000

[0001]                      Subtable Type : 0C [Generic Interrupt Distributor]
[0001]                             Length : 18
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000000
[0008]                       Base Address : 000000002C001000 /* armv8 foundation model's GIC distributor base addr */
[0004]                     Interrupt Base : 00000000
[0004]                           Reserved : 00000000
