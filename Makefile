MABDIR := tools/mab/
PLATDIR := platforms/

%.acpi : ${MABDIR}/mab
	make MAB=${CURDIR}/${MABDIR}/mab -C $(PLATDIR) $@

${MABDIR}/mab :
	make -C ${MABDIR}

clean :
	make -C ${MABDIR} clean
	make -C ${PLATDIR} clean

