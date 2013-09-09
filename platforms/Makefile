ifdef PADDR
	PADDR_ARG := -p $(PADDR)
endif

%.acpi : FORCE
	$(MAB) -d $@ $(PADDR_ARG) -i $(basename $@).manifest -o $@
ifdef APEI
	$(BFAPEI) -d $@ -i $(basename $@).manifest -t $(APEI) -o apei.acpi
endif

clean :
	-rm -f *.acpi/*.aml
	-rm -f *.acpi/*.lst
	-rm -f *.acpi/*.acpi

FORCE :

