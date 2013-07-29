/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
 * 
 * [MCHI] Management Controller Host Interface Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 * This source released under the terms of the GPLv2.
 */

[0004]                          Signature : "MCHI"
[0004]                       Table Length : 00000045
[0001]                           Revision : 01
[0001]                           Checksum : E4
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "ARNDALE "
[0004]                       Oem Revision : 02000715
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0001]                     Interface Type : 01
[0001]                           Protocol : 00
[0008]                      Protocol Data : 0000000000000000
[0001]                     Interrupt Type : 00
[0001]                                Gpe : 00
[0001]                    Pci Device Flag : 00
[0004]                   Global Interrupt : 00000000

[0012]                   Control Register : [Generic Address Structure]
[0001]                           Space ID : 02 [PCI_Config]
[0001]                          Bit Width : 08
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 00 [Undefined/Legacy]
[0008]                            Address : 0000000000000000

[0001]                        Pci Segment : 00
[0001]                            Pci Bus : 00
[0001]                         Pci Device : 00
[0001]                       Pci Function : 00
