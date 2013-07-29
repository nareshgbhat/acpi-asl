/*
 * Intel ACPI Component Architecture
 * iASL Compiler/Disassembler version 20130117-64 [Jan 31 2013]
 * Copyright (c) 2000 - 2013 Intel Corporation
 * 
 * Template for [WDDT] ACPI Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 */

[0004]                          Signature : "WDDT"    [Watchdog Description Table]
[0004]                       Table Length : 00000040
[0001]                           Revision : 01
[0001]                           Checksum : 00
[0006]                             Oem ID : "INTEL "
[0008]                       Oem Table ID : "TEMPLATE"
[0004]                       Oem Revision : 00000000
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0002]              Specification Version : 0000
[0002]                      Table Version : 0000
[0002]                      PCI Vendor ID : 0000

[0012]                     Timer Register : [Generic Address Structure]
[0001]                           Space ID : 01 [SystemIO]
[0001]                          Bit Width : FF
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 00 [Undefined/Legacy]
[0008]                            Address : 0000000000000000

[0002]                          Max Count : 0000
[0002]                          Min Count : 0000
[0002]                             Period : 0000
[0002]             Status (decoded below) : 0000
                                Available : 0
                                   Active : 0
                                  OS Owns : 0
                               User Reset : 0
                            Timeout Reset : 0
                         Power Fail Reset : 0
                            Unknown Reset : 0
[0002]         Capability (decoded below) : 0000
                               Auto Reset : 0
                            Timeout Alert : 0
