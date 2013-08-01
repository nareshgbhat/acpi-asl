MABDIR := tools/mab/
PLATDIR := platforms/

%.acpi : $(MABDIR)/mab
	make MAB=$(CURDIR)/$(MABDIR)/mab PADDR=$(PADDR) -C $(PLATDIR) $@

$(MABDIR)/mab : FORCE
	make -C $(MABDIR)

clean :
	make -C $(MABDIR) clean
	make -C $(PLATDIR) clean

FORCE :
