/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright 
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the 
 * documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * 
 * NB: This License is also known as the "BSD 2-Clause License".
 *
 * Template for [ASF!] ACPI Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 */

[0004]                          Signature : "ASF!"
[0004]                       Table Length : 00000072
[0001]                           Revision : 10
[0001]                           Checksum : 0B
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "ARNDALE "
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0001]                      Subtable Type : 00 [ASF Information]
[0001]                           Reserved : 00
[0002]                             Length : 0010
[0001]                Minimum Reset Value : 00
[0001]           Minimum Polling Interval : 00
[0002]                          System ID : 0000
[0004]                    Manufacturer ID : 00000000
[0001]                              Flags : 00
[0003]                           Reserved : 000000

[0001]                      Subtable Type : 01 [ASF Alerts]
[0001]                           Reserved : 00
[0002]                             Length : 0014
[0001]                         AssertMask : 00
[0001]                       DeassertMask : 00
[0001]                        Alert Count : 01
[0001]                  Alert Data Length : 0C

[0001]                            Address : 00
[0001]                            Command : 00
[0001]                               Mask : 00
[0001]                              Value : 00
[0001]                         SensorType : 00
[0001]                               Type : 00
[0001]                             Offset : 00
[0001]                         SourceType : 00
[0001]                           Severity : 00
[0001]                       SensorNumber : 00
[0001]                             Entity : 00
[0001]                           Instance : 00

[0001]                      Subtable Type : 02 [ASF Remote Control]
[0001]                           Reserved : 00
[0002]                             Length : 000C
[0001]                      Control Count : 01
[0001]                Control Data Length : 04
[0002]                           Reserved : 0000

[0001]                           Function : 00
[0001]                            Address : 00
[0001]                            Command : 00
[0001]                              Value : 00

[0001]                      Subtable Type : 03 [ASF RMCP Boot Options]
[0001]                           Reserved : 00
[0002]                             Length : 0017
[0007]                       Capabilities : 00 00 00 00 00 00 00
[0001]                    Completion Code : 00
[0004]                      Enterprise ID : 00000000
[0001]                            Command : 00
[0002]                          Parameter : 0000
[0002]                       Boot Options : 0000
[0002]                     Oem Parameters : 0000

[0001]                      Subtable Type : 84 [ASF Address]
[0001]                           Reserved : 00
[0002]                             Length : 0007
[0001]                      Eprom Address : 00
[0001]                       Device Count : 01
[0001]                          Addresses : 00 

