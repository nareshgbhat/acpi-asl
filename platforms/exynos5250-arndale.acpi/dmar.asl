/*
 * Intel ACPI Component Architecture
 * iASL Compiler/Disassembler version 20130117-64 [Jan 31 2013]
 * Copyright (c) 2000 - 2013 Intel Corporation
 * 
 * Template for [DMAR] ACPI Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 */

[0004]                          Signature : "DMAR"    [DMA Remapping table]
[0004]                       Table Length : 0000008C
[0001]                           Revision : 01
[0001]                           Checksum : 15
[0006]                             Oem ID : "INTEL "
[0008]                       Oem Table ID : "TEMPLATE"
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0001]                 Host Address Width : 2F
[0001]                              Flags : 01

[0002]                      Subtable Type : 0000 [Hardware Unit Definition]
[0002]                             Length : 0018
[0001]                              Flags : 01
[0001]                           Reserved : 00
[0002]                 PCI Segment Number : 0000
[0008]              Register Base Address : 00000000FD020000

[0001]            Device Scope Entry Type : 03
[0001]                       Entry Length : 08
[0002]                           Reserved : 0000
[0001]                     Enumeration ID : 08
[0001]                     PCI Bus Number : F0
[0002]                           PCI Path : 1F,07

[0002]                      Subtable Type : 0001 [Reserved Memory Region]
[0002]                             Length : 0020
[0002]                           Reserved : 0000
[0002]                 PCI Segment Number : 0000
[0008]                       Base Address : 0000000078C21000
[0008]                End Address (limit) : 0000000078C23FFF

[0001]            Device Scope Entry Type : 01
[0001]                       Entry Length : 08
[0002]                           Reserved : 0000
[0001]                     Enumeration ID : 00
[0001]                     PCI Bus Number : 00
[0002]                           PCI Path : 1D,00

[0002]                      Subtable Type : 0002 [Root Port ATS Capability]
[0002]                             Length : 0010
[0001]                              Flags : 00
[0001]                           Reserved : 00
[0002]                 PCI Segment Number : 0000

[0001]            Device Scope Entry Type : 02
[0001]                       Entry Length : 08
[0002]                           Reserved : 0000
[0001]                     Enumeration ID : 00
[0001]                     PCI Bus Number : 00
[0002]                           PCI Path : 01,00

[0002]                      Subtable Type : 0003 [Remapping Hardware Static Affinity]
[0002]                             Length : 0014
[0004]                           Reserved : 00000000
[0008]                       Base Address : 00000000FD020000
[0004]                   Proximity Domain : 00000000
