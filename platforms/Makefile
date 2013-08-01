%.acpi : FORCE
	$(MAB) -d $@ -i $(basename $@).manifest -o $@

clean :
	-rm *.acpi/*.aml
	-rm *.acpi/*.lst
	-rm *.acpi/*.acpi

FORCE :

