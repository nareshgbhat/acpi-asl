ifdef PADDR
	PADDR_ARG := -p $(PADDR)
endif

%.acpi : FORCE
	$(MAB) -d $@ $(PADDR_ARG) -i $(basename $@).manifest -o $@

clean :
	-rm *.acpi/*.aml
	-rm *.acpi/*.lst
	-rm *.acpi/*.acpi

FORCE :

