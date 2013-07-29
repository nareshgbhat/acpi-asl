/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org
 * 
 * [SPMI] Server Platform Management Interface Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 * This source is released under the terms of the GPLv2.
 */

[0004]                          Signature : "SPMI"
[0004]                       Table Length : 00000041
[0001]                           Revision : 04
[0001]                           Checksum : ED
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "ARNDALE "
[0004]                       Oem Revision : 00000000
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0001]                     Interface Type : 00
[0001]                           Reserved : 00
[0002]                  IPMI Spec Version : 0000
[0001]                     Interrupt Type : 00
[0001]                         GPE Number : 00
[0001]                           Reserved : 00
[0001]                    PCI Device Flag : 00
[0004]                          Interrupt : 00000000

[0012]                      IPMI Register : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 08
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 01 [Byte Access:8]
[0008]                            Address : 0000000000000000

[0001]                        PCI Segment : 00
[0001]                            PCI Bus : 00
[0001]                         PCI Device : 00
[0001]                       PCI Function : 00
[0001]                           Reserved : 00
