/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
 * 
 * [PMTT] Platform Memory Topology Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 * This source is released under the terms of the GPLv2.
 */

[0004]                          Signature : "PMTT"
[0004]                       Table Length : 000000B4
[0001]                           Revision : 01
[0001]                           Checksum : 3A
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "ARNDALE "
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20110826

[0004]                           Reserved : 00000000

[0001]                      Subtable Type : 00 [Socket]
[0001]                           Reserved : 00
[0002]                             Length : 0080
[0002]              Flags (decoded below) : 0001
                         Top-level Device : 1
                         Physical Element : 0
                              Memory Type : 0
[0002]                           Reserved : 0000
[0002]                          Socket ID : 0000
[0002]                           Reserved : 0000

[0001]                      Subtable Type : 01 [Memory Controller]
[0001]                           Reserved : 00
[0002]                             Length : 0054
[0002]              Flags (decoded below) : 0005
                         Top-level Device : 1
                         Physical Element : 0
                              Memory Type : 1
[0002]                           Reserved : 0000
[0004]                       Read Latency : 00000000
[0004]                      Write Latency : 00000000
[0004]                     Read Bandwidth : 00000000
[0004]                    Write Bandwidth : 00000000
[0002]                       Access Width : 0000
[0002]                          Alignment : 0000
[0002]                           Reserved : 0000
[0002]                       Domain Count : 0003
[0004]                   Proximity Domain : 00000000
[0004]                   Proximity Domain : 00000000
[0004]                   Proximity Domain : 00000000

[0001]                      Subtable Type : 02 [Physical Component (DIMM)]
[0001]                           Reserved : 00
[0002]                             Length : 0014
[0002]              Flags (decoded below) : 0002
                         Top-level Device : 0
                         Physical Element : 1
                              Memory Type : 0
[0002]                           Reserved : 0000
[0002]                       Component ID : 0000
[0002]                           Reserved : 0000
[0004]                        Memory Size : 00000000
[0004]                        Bios Handle : 00000000

[0001]                      Subtable Type : 02 [Physical Component (DIMM)]
[0001]                           Reserved : 00
[0002]                             Length : 0014
[0002]              Flags (decoded below) : 0002
                         Top-level Device : 0
                         Physical Element : 1
                              Memory Type : 0
[0002]                           Reserved : 0000
[0002]                       Component ID : 0000
[0002]                           Reserved : 0000
[0004]                        Memory Size : 00000000
[0004]                        Bios Handle : 00000000

[0001]                      Subtable Type : 01 [Memory Controller]
[0001]                           Reserved : 00
[0002]                             Length : 0020
[0002]              Flags (decoded below) : 0001
                         Top-level Device : 1
                         Physical Element : 0
                              Memory Type : 0
[0002]                           Reserved : 0000
[0004]                       Read Latency : 00000000
[0004]                      Write Latency : 00000000
[0004]                     Read Bandwidth : 00000000
[0004]                    Write Bandwidth : 00000000
[0002]                       Access Width : 0000
[0002]                          Alignment : 0000
[0002]                           Reserved : 0000
[0002]                       Domain Count : 0000

[0001]                      Subtable Type : 00 [Socket]
[0001]                           Reserved : 00
[0002]                             Length : 000C
[0002]              Flags (decoded below) : 0001
                         Top-level Device : 1
                         Physical Element : 0
                              Memory Type : 0
[0002]                           Reserved : 0000
[0002]                          Socket ID : 0000
[0002]                           Reserved : 0000
