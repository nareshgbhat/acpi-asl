/*
 * Intel ACPI Component Architecture
 * iASL Compiler/Disassembler version 20130117-64 [Jan 31 2013]
 * Copyright (c) 2000 - 2013 Intel Corporation
 * 
 * Template for [DBGP] ACPI Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 */

[0004]                          Signature : "DBGP"    [Debug Port table]
[0004]                       Table Length : 00000034
[0001]                           Revision : 01
[0001]                           Checksum : 1A
[0006]                             Oem ID : "INTEL "
[0008]                       Oem Table ID : "TEMPLATE"
[0004]                       Oem Revision : 00000000
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0001]                     Interface Type : 00
[0003]                           Reserved : 000000

[0012]                Debug Port Register : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 08
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 00 [Undefined/Legacy]
[0008]                            Address : 0000000000000000

