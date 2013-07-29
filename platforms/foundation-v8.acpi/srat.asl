/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
 * 
 * [SRAT] System Resource Affinity Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 * This source is released under the terms of the GPLv2.
 */

[0004]                          Signature : "SRAT"
[0004]                       Table Length : 00000080
[0001]                           Revision : 03
[0001]                           Checksum : 5A
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "FOUNDATI"
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0004]                     Table Revision : 00000001
[0008]                           Reserved : 0000000000000000

[0001]                      Subtable Type : 00 [Processor Local APIC/SAPIC Affinity]
[0001]                             Length : 10

[0001]            Proximity Domain Low(8) : 00
[0001]                            Apic ID : 00
[0004]              Flags (decoded below) : 00000001
                                  Enabled : 1
[0001]                    Local Sapic EID : 00
[0003]          Proximity Domain High(24) : 000000
[0004]                           Reserved : 00000000

[0001]                      Subtable Type : 01 [Memory Affinity]
[0001]                             Length : 28

[0004]                   Proximity Domain : 00000000
[0002]                          Reserved1 : 0000
[0008]                       Base Address : 0000000000000000
[0008]                     Address Length : 000000000009FC00
[0004]                          Reserved2 : 00000000
[0004]              Flags (decoded below) : 00000001
                                  Enabled : 1
                            Hot Pluggable : 0
                             Non-Volatile : 0
[0008]                          Reserved3 : 0000000000000000

[0001]                      Subtable Type : 02 [Processor Local x2APIC Affinity]
[0001]                             Length : 18

[0002]                          Reserved1 : 0000
[0004]                   Proximity Domain : 00000000
[0004]                            Apic ID : 00000000
[0004]              Flags (decoded below) : 00000001
                                  Enabled : 1
[0004]                       Clock Domain : 00000000
[0004]                          Reserved2 : 00000000
