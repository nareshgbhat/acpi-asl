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
[0008]                       Oem Table ID : "ARNDALE "
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20110623

[0004]                 Local Apic Address : 00000000
[0004]              Flags (decoded below) : 00000001
                      PC-AT Compatibility : 1

[0001]                      Subtable Type : 00 [Processor Local APIC]
[0001]                             Length : 08
[0001]                       Processor ID : 00
[0001]                      Local Apic ID : 00
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1

[0001]                      Subtable Type : 01 [I/O APIC]
[0001]                             Length : 0C
[0001]                        I/O Apic ID : 01
[0001]                           Reserved : 00
[0004]                            Address : 00000000
[0004]                          Interrupt : 00000000

[0001]                      Subtable Type : 02 [Interrupt Source Override]
[0001]                             Length : 0A
[0001]                                Bus : 00
[0001]                             Source : 00
[0004]                          Interrupt : 00000000
[0002]              Flags (decoded below) : 0000
                                 Polarity : 0
                             Trigger Mode : 0

[0001]                      Subtable Type : 03 [NMI Source]
[0001]                             Length : 08
[0002]              Flags (decoded below) : 000D
                                 Polarity : 1
                             Trigger Mode : 3
[0004]                          Interrupt : 00000001

[0001]                      Subtable Type : 04 [Local APIC NMI]
[0001]                             Length : 06
[0001]                       Processor ID : 00
[0002]              Flags (decoded below) : 0005
                                 Polarity : 1
                             Trigger Mode : 1
[0001]               Interrupt Input LINT : 01

[0001]                      Subtable Type : 05 [Local APIC Address Override]
[0001]                             Length : 0C
[0002]                           Reserved : 0000
[0008]                       APIC Address : 0000000000000000

[0001]                      Subtable Type : 06 [I/O SAPIC]
[0001]                             Length : 10
[0001]                       I/O Sapic ID : 00
[0001]                           Reserved : 00
[0004]                     Interrupt Base : 00000000
[0008]                            Address : 0000000000000000

[0001]                      Subtable Type : 07 [Local SAPIC]
[0001]                             Length : 16
[0001]                       Processor ID : 00
[0001]                     Local Sapic ID : 00
[0001]                    Local Sapic EID : 00
[0003]                           Reserved : 000000
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]                      Processor UID : 00000000
[0006]               Processor UID String : "\CPU0"

[0001]                      Subtable Type : 08 [Platform Interrupt Sources]
[0001]                             Length : 10
[0002]              Flags (decoded below) : 0005
                                 Polarity : 1
                             Trigger Mode : 1
[0001]                      InterruptType : 00
[0001]                       Processor ID : 00
[0001]                      Processor EID : 00
[0001]                   I/O Sapic Vector : 00
[0004]                          Interrupt : 00000001
[0004]              Flags (decoded below) : 00000001
                            CPEI Override : 1

[0001]                      Subtable Type : 09 [Processor Local x2APIC]
[0001]                             Length : 10
[0002]                           Reserved : 0000
[0004]                Processor x2Apic ID : 00000000
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]                      Processor UID : 00000000

[0001]                      Subtable Type : 0A [Local x2APIC NMI]
[0001]                             Length : 0C
[0002]              Flags (decoded below) : 0005
                                 Polarity : 1
                             Trigger Mode : 1
[0004]                      Processor UID : 00000000
[0001]               Interrupt Input LINT : 00
[0003]                           Reserved : 000000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000000
[0004]                      Processor UID : 00000000
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]           Parking Protocol Version : 00000000
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 0000000000000000
[0008]                       Base Address : 0000000000000000

[0001]                      Subtable Type : 0C [Generic Interrupt Distributor]
[0001]                             Length : 18
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000000
[0008]                       Base Address : 0000000000000000
[0004]                     Interrupt Base : 00000000
[0004]                           Reserved : 00000000
