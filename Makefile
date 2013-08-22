MABDIR := tools/mab/
CABDIR := tools/cab/
PLATDIR := platforms/

%.acpi : $(MABDIR)/mab $(CABDIR)/cab
	make MAB=$(CURDIR)/$(MABDIR)/mab PADDR=$(PADDR) -C $(PLATDIR) $@

$(MABDIR)/mab : FORCE
	make -C $(MABDIR)

$(CABDIR)/cab : FORCE
	make -C $(CABDIR)

clean :
	make -C $(MABDIR) clean
	make -C $(CABDIR) clean
	make -C $(PLATDIR) clean

FORCE :
