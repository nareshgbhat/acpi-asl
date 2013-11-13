#
# Copyright (c) 2013, Al Stone <al.stone@linaro.org>
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
# 1. Redistributions of source code must retain the above copyright 
# notice, this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the 
# documentation and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
# TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# 
# NB: This License is also known as the "BSD 2-Clause License".
#

MABDIR := tools/mab/
CABDIR := tools/cab/
BFAPEI_DIR := tools/bfapei/
COMMON_DIR := tools/common/
PLATDIR := platforms/

ARGS := MAB=$(CURDIR)/$(MABDIR)/mab PADDR=$(PADDR)
ifdef APEI
	ARGS += BFAPEI=$(CURDIR)/$(BFAPEI_DIR)/bfapei APEI=$(APEI)
endif

%.acpi : mab cab bfapei
	make $(ARGS) -C $(PLATDIR) $@

mab : FORCE
	make -C $(MABDIR) PROG=mab

cab : FORCE
	make -C $(CABDIR) PROG=cab

bfapei : FORCE
	make -C $(BFAPEI_DIR) PROG=bfapei

clean :
	make -C $(MABDIR) clean PROG=mab
	make -C $(CABDIR) clean PROG=cab
	make -C $(BFAPEI_DIR) clean PROG=bfapei
	make -C $(COMMON_DIR) clean
	make -C $(PLATDIR) clean

FORCE :
