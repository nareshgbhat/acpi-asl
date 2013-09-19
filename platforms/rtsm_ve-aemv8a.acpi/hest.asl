/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org
 *
 * [HEST] Hardware Error Source Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 * This source is released under the terms of the GPLv2.
 */

[0004]                          Signature : "HEST"
[0004]                       Table Length : 000001D4
[0001]                           Revision : 01
[0001]                           Checksum : 20
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "RTSMVEV8"
[0004]                       Oem Revision : 00000002
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0004]                 Error Source Count : 00000001

[0002]                      Subtable Type : 0009 [Generic Hardware Error Source]
[0002]                          Source Id : 0002
[0002]                  Related Source Id : FFFF
[0001]                           Reserved : 00
[0001]                            Enabled : 01
[0004]             Records To Preallocate : 00000001
[0004]            Max Sections Per Record : 00000001
[0004]                Max Raw Data Length : 00001000

[0012]               Error Status Address : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0000

[0028]                             Notify : [Hardware Error Notification Structure]
[0001]                        Notify Type : 03 [SCI]
[0001]                      Notify Length : 1C
[0002]         Configuration Write Enable : 0000
[0004]                       PollInterval : 00000000
[0004]                             Vector : 00000000
[0004]            Polling Threshold Value : 00000000
[0004]           Polling Threshold Window : 00000000
[0004]              Error Threshold Value : 00000000
[0004]             Error Threshold Window : 00000000

[0004]          Error Status Block Length : 00001000
