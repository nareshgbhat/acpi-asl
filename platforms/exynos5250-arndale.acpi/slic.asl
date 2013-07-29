/*
 * Intel ACPI Component Architecture
 * iASL Compiler/Disassembler version 20130117-64 [Jan 31 2013]
 * Copyright (c) 2000 - 2013 Intel Corporation
 * 
 * Template for [SLIC] ACPI Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 */

[0004]                          Signature : "SLIC"    [Software Licensing Description Table]
[0004]                       Table Length : 00000176
[0001]                           Revision : 01
[0001]                           Checksum : 07
[0006]                             Oem ID : "INTEL "
[0008]                       Oem Table ID : "TEMPLATE"
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20110211


[0004]                      Subtable Type : 00000000 [Public Key Structure]
[0004]                             Length : 0000009C

[0001]                           Key Type : 06
[0001]                            Version : 02
[0002]                           Reserved : 0000
[0004]                          Algorithm : 00002400
[0004]                              Magic : "RSA1"
[0004]                          BitLength : 00000400
[0004]                           Exponent : 00000000
[0128]                            Modulus : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

[0004]                      Subtable Type : 00000001 [Windows Marker Structure]
[0004]                             Length : 000000B6

[0004]                            Version : 00020000
[0006]                             Oem ID : "INTEL "
[0008]                       Oem Table ID : "TEMPLATE"
[0008]                       Windows Flag : "WINDOWS "
[0004]                       SLIC Version : 00020001
[0016]                           Reserved : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
[0128]                          Signature : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
                                            00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
