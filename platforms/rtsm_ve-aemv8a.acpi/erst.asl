/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
 *
 * [ERST] Error Record Serialization Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 * This source released under the terms of the GPLv2.
 */

[0004]                          Signature : "ERST"
[0004]                       Table Length : 00000230
[0001]                           Revision : 01
[0001]                           Checksum : AB
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "RTSMVEV8"
[0004]                       Oem Revision : 00000002
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0004]        Serialization Header Length : 00000030
[0004]                           Reserved : 00000000
[0004]            Instruction Entry Count : 00000010

[0001]                             Action : 00 [Begin Write Operation]
[0001]                        Instruction : 03 [Write Register Value]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0100

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 01 [Begin Read Operation]
[0001]                        Instruction : 03 [Write Register Value]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0108

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 02 [Begin Clear Operation]
[0001]                        Instruction : 03 [Write Register Value]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0110

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 03 [End Operation]
[0001]                        Instruction : 04 [Noop]
[0001]              Flags (decoded below) : 01
                   Preserve Register Bits : 1
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0118

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 04 [Set Record Offset]
[0001]                        Instruction : 02 [Write Register]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0120

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 05 [Execute Operation]
[0001]                        Instruction : 03 [Write Register Value]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 08
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 01 [Byte Access:8]
[0008]                            Address : 0xFFFF0128

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 06 [Check Busy Status]
[0001]                        Instruction : 01 [Read Register Value]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0130

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 07 [Get Command Status]
[0001]                        Instruction : 00 [Read Register]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0138

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 08 [Get Record Identifier]
[0001]                        Instruction : 00 [Read Register]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0140

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 09 [Set Record Identifier]
[0001]                        Instruction : 02 [Write Register]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0148

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 0A [Get Record Count]
[0001]                        Instruction : 00 [Read Register]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0150

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 0B [Begin Dummy Write]
[0001]                        Instruction : 03 [Write Register Value]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0158

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 0C [Unused/Unknown Action]
[0001]                        Instruction : 00 [Read Register]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0160

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 0D [Get Error Address Range]
[0001]                        Instruction : 00 [Read Register]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0168

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 0E [Get Error Address Length]
[0001]                        Instruction : 00 [Read Register]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0170

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 0F [Get Error Attributes]
[0001]                        Instruction : 00 [Read Register]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0178

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF
