/*
 * Intel ACPI Component Architecture
 * iASL Compiler/Disassembler version 20130117-64 [Jan 31 2013]
 * Copyright (c) 2000 - 2013 Intel Corporation
 * 
 * Template for [WDAT] ACPI Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 */

[0004]                          Signature : "WDAT"    [Watchdog Action Table]
[0004]                       Table Length : 0000005C
[0001]                           Revision : 01
[0001]                           Checksum : E3
[0006]                             Oem ID : "INTEL "
[0008]                       Oem Table ID : "TEMPLATE"
[0004]                       Oem Revision : 00000000
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0004]                      Header Length : 00000020
[0002]                        PCI Segment : 00FF
[0001]                            PCI Bus : FF
[0001]                         PCI Device : FF
[0001]                       PCI Function : FF
[0003]                           Reserved : 000000
[0004]                       Timer Period : 00000258
[0004]                          Max Count : 000003FF
[0004]                          Min Count : 00000002
[0001]              Flags (decoded below) : 00
                                  Enabled : 0
                      Stopped When Asleep : 0
[0003]                           Reserved : 000000
[0004]               Watchdog Entry Count : 0000000E

[0001]                    Watchdog Action : 01
[0001]                        Instruction : 02
[0002]                           Reserved : 0000

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 01 [SystemIO]
[0001]                          Bit Width : 10
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 02 [Word Access:16]
[0008]                            Address : 0000000000000460

[0004]                              Value : 00000001
[0004]                      Register Mask : 00000001
