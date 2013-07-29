/*
 * Intel ACPI Component Architecture
 * iASL Compiler/Disassembler version 20130117-64 [Jan 31 2013]
 * Copyright (c) 2000 - 2013 Intel Corporation
 * 
 * Template for [IVRS] ACPI Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 */

[0004]                          Signature : "IVRS"    [I/O Virtualization Reporting Structure]
[0004]                       Table Length : 000000BC
[0001]                           Revision : 01
[0001]                           Checksum : 87
[0006]                             Oem ID : "INTEL "
[0008]                       Oem Table ID : "TEMPLATE"
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0004]                Virtualization Info : 00000000
[0008]                           Reserved : 0000000000000000

[0001]                      Subtable Type : 10 [Hardware Definition Block]
[0001]                              Flags : 14
[0002]                             Length : 0034
[0002]                           DeviceId : 0000

[0002]                  Capability Offset : 0000
[0008]                       Base Address : 0000000000000000
[0002]                  PCI Segment Group : 0000
[0002]                Virtualization Info : 0000
[0004]                           Reserved : 00000000

[0001]                         Entry Type : 00
[0002]                          Device ID : 0000
[0001]                       Data Setting : 00

[0001]                         Entry Type : 40
[0002]                          Device ID : 0000
[0001]                       Data Setting : 00
[0004]                      Extended Data : 00000000

[0001]                         Entry Type : 42
[0002]                          Device ID : 0000
[0001]                       Data Setting : 00
[0001]                           Reserved : 00
[0002]              Source Used Device ID : 0000
[0001]                           Reserved : 00

[0001]                         Entry Type : 48
[0002]                          Device ID : 0000
[0001]                       Data Setting : 00
[0001]                             Handle : 00
[0002]              Source Used Device ID : 0000
[0001]                            Variety : 00

[0001]                      Subtable Type : 20 [Memory Definition Block]
[0001]                              Flags : 08
[0002]                             Length : 0020
[0002]                           DeviceId : 0000

[0002]                     Auxiliary Data : 0000
[0008]                           Reserved : 0000000000000000
[0008]                      Start Address : 0000000000000000
[0008]                      Memory Length : 0000000000000000

[0001]                      Subtable Type : 21 [Memory Definition Block]
[0001]                              Flags : 04
[0002]                             Length : 0020
[0002]                           DeviceId : 0000

[0002]                     Auxiliary Data : 0000
[0008]                           Reserved : 0000000000000000
[0008]                      Start Address : 0000000000000000
[0008]                      Memory Length : 0000000000000000

[0001]                      Subtable Type : 10 [Hardware Definition Block]
[0001]                              Flags : 14
[0002]                             Length : 0018
[0002]                           DeviceId : 0000

[0002]                  Capability Offset : 0000
[0008]                       Base Address : 0000000000000000
[0002]                  PCI Segment Group : 0000
[0002]                Virtualization Info : 0000
[0004]                           Reserved : 00000000
