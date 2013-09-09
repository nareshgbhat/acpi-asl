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
