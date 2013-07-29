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
[0008]                       Oem Table ID : "ARNDALE "
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0004]                 Error Source Count : 00000004

[0002]                      Subtable Type : 0000 [IA-32 Machine Check Exception]
[0002]                          Source Id : 0000
[0002]                          Reserved1 : 0000
[0001]              Flags (decoded below) : 00
                           Firmware First : 0
[0001]                            Enabled : 01
[0004]             Records To Preallocate : 00000001
[0004]            Max Sections Per Record : 00000001
[0008]             Global Capability Data : 0000000000000000
[0008]                Global Control Data : 0000000000000000
[0001]                 Num Hardware Banks : 02
[0007]                          Reserved2 : 00000000000000

[0001]                        Bank Number : 00
[0001]               Clear Status On Init : 00
[0001]                      Status Format : 00
[0001]                           Reserved : 00
[0004]                   Control Register : 00000000
[0008]                       Control Data : 0000000000000000
[0004]                    Status Register : 00000000
[0004]                   Address Register : 00000000
[0004]                      Misc Register : 00000000

[0001]                        Bank Number : 01
[0001]               Clear Status On Init : 00
[0001]                      Status Format : 00
[0001]                           Reserved : 00
[0004]                   Control Register : 00000000
[0008]                       Control Data : 0000000000000000
[0004]                    Status Register : 00000000
[0004]                   Address Register : 00000000
[0004]                      Misc Register : 00000000

[0002]                      Subtable Type : 0001 [IA-32 Corrected Machine Check]
[0002]                          Source Id : 0001
[0002]                          Reserved1 : 0000
[0001]              Flags (decoded below) : 00
                           Firmware First : 0
[0001]                            Enabled : 01
[0004]             Records To Preallocate : 00000001
[0004]            Max Sections Per Record : 00000001

[0028]                             Notify : [Hardware Error Notification Structure]
[0001]                        Notify Type : 00 [Polled]
[0001]                      Notify Length : 00
[0002]         Configuration Write Enable : 0000
[0004]                       PollInterval : 00000000
[0004]                             Vector : 00000000
[0004]            Polling Threshold Value : 00000000
[0004]           Polling Threshold Window : 00000000
[0004]              Error Threshold Value : 00000000
[0004]             Error Threshold Window : 00000000

[0001]                 Num Hardware Banks : 02
[0003]                          Reserved2 : 000000

[0001]                        Bank Number : 00
[0001]               Clear Status On Init : 00
[0001]                      Status Format : 00
[0001]                           Reserved : 00
[0004]                   Control Register : 00000000
[0008]                       Control Data : 0000000000000000
[0004]                    Status Register : 00000000
[0004]                   Address Register : 00000000
[0004]                      Misc Register : 00000000

[0001]                        Bank Number : 01
[0001]               Clear Status On Init : 00
[0001]                      Status Format : 00
[0001]                           Reserved : 00
[0004]                   Control Register : 00000000
[0008]                       Control Data : 0000000000000000
[0004]                    Status Register : 00000000
[0004]                   Address Register : 00000000
[0004]                      Misc Register : 00000000

[0002]                      Subtable Type : 0007 [PCI Express AER (AER Endpoint)]
[0002]                          Source Id : 0000
[0002]                           Reserved : 0000
[0001]              Flags (decoded below) : 00
                           Firmware First : 0
[0001]                            Enabled : 01
[0004]             Records To Preallocate : 00000001
[0004]            Max Sections Per Record : 00000001
[0004]                                Bus : 00000000
[0002]                             Device : 0000
[0002]                           Function : 0000
[0002]                      DeviceControl : 0000
[0002]                           Reserved : 0000
[0004]                 Uncorrectable Mask : 00000000
[0004]             Uncorrectable Severity : 00000000
[0004]                   Correctable Mask : 00000000
[0004]              Advanced Capabilities : 00000000

[0002]                      Subtable Type : 0008 [PCI Express/PCI-X Bridge AER]
[0002]                          Source Id : 0000
[0002]                           Reserved : 0000
[0001]              Flags (decoded below) : 00
                           Firmware First : 0
[0001]                            Enabled : 01
[0004]             Records To Preallocate : 00000001
[0004]            Max Sections Per Record : 00000001
[0004]                                Bus : 00000000
[0002]                             Device : 0000
[0002]                           Function : 0000
[0002]                      DeviceControl : 0000
[0002]                           Reserved : 0000
[0004]                 Uncorrectable Mask : 00000000
[0004]             Uncorrectable Severity : 00000000
[0004]                   Correctable Mask : 00000000
[0004]              Advanced Capabilities : 00000000
[0004]             2nd Uncorrectable Mask : 00000000
[0004]         2nd Uncorrectable Severity : 00000000
[0004]          2nd Advanced Capabilities : 00000000

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
[0008]                            Address : 0000000000000000

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

[0002]                      Subtable Type : 0009 [Generic Hardware Error Source]
[0002]                          Source Id : 0003
[0002]                  Related Source Id : 0000
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
[0008]                            Address : 0000000000000000

[0028]                             Notify : [Hardware Error Notification Structure]
[0001]                        Notify Type : 04 [NMI]
[0001]                      Notify Length : 1C
[0002]         Configuration Write Enable : 0000
[0004]                       PollInterval : 00000000
[0004]                             Vector : 00000000
[0004]            Polling Threshold Value : 00000000
[0004]           Polling Threshold Window : 00000000
[0004]              Error Threshold Value : 00000000
[0004]             Error Threshold Window : 00000000

[0004]          Error Status Block Length : 00001000
