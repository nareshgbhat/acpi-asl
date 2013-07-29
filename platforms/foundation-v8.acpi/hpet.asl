/*
 * Intel ACPI Component Architecture
 * iASL Compiler/Disassembler version 20130117-64 [Jan 31 2013]
 * Copyright (c) 2000 - 2013 Intel Corporation
 * 
 * Template for [HPET] ACPI Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 */

[0004]                          Signature : "HPET"    [High Precision Event Timer table]
[0004]                       Table Length : 00000038
[0001]                           Revision : 01
[0001]                           Checksum : 09
[0006]                             Oem ID : "INTEL "
[0008]                       Oem Table ID : "TEMPLATE"
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0004]                  Hardware Block ID : 00000000

[0012]               Timer Block Register : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 00
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 00 [Undefined/Legacy]
[0008]                            Address : 0000000000000000

[0001]                    Sequence Number : 00
[0002]                Minimum Clock Ticks : 0000
[0001]              Flags (decoded below) : 00
                          4K Page Protect : 0
                         64K Page Protect : 0
