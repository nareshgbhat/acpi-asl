MABDIR := tools/mab/
CABDIR := tools/cab/
COMMON_DIR := tools/common/
PLATDIR := platforms/

%.acpi : mab cab
	make MAB=$(CURDIR)/$(MABDIR)/mab PADDR=$(PADDR) -C $(PLATDIR) $@

mab : FORCE
	make -C $(MABDIR) PROG=mab

cab : FORCE
	make -C $(CABDIR) PROG=cab

clean :
	make -C $(MABDIR) clean PROG=mab
	make -C $(CABDIR) clean PROG=cab
	make -C $(COMMON_DIR) clean
	make -C $(PLATDIR) clean

FORCE :
