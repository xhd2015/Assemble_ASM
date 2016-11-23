
name := bootsect
#the support file is in a specific order
support := bootsect_head memcopy LBA28 bootsect_tail
suffix := c o elf img
ccflag-pure-asm := -fno-asynchronous-unwind-tables
ccflag-asm-default := -m32 -S

generated16_o := $(patsubst %,%16.o,$(support))
generated16_s := $(patsubst %,%16.s,$(support))

.PHONY: view_codes see_doc help include_once clean
.ONESHELL:
help:
	@
	echo "@depreciated opt=pure-asm is suppored no longer."
	echo "you can pass opt to make,like make Target opt=?.\
	The avaible opt are opt=[pure-asm],opt=pure-asm will generate\
	a pure assemble code from c codes,without any extra information(say,debug information and unwind tables)."
	echo "make include_once file=? ==> generate the include once declarement"
see_doc:
	@
	cat a_summ*

view_codes:$(name).img
	@
	objdump -D -m i8086 -b binary $(name).img
.ONESHELL:
include_once:
	@	
	orifile=$(file)
	file=$${orifile:?missing option file=?}	
	file=$${file%.*}
	file=$$(python3 -c "x='$${file}';x=x.upper().replace('.','_');print(x)")
	file=__$${file}_H__
	echo "//=========FILE: $${orifile}======"
	echo "#ifndef $${file} /*START this file,define once*/"
	echo "#define $${file}"
	echo
	echo "#endif /*END this file*/"


.ONESHELL:
$(name).s:bootsect_head16.s bootsect_tail16.s
	cat bootsect_head16.s bootsect_tail16.s > $(name).s

.SECONDEXPANSION:
$(generated16_s):$$(patsubst %16.s,%.c,$$@)
	gcc -m32 $(ccflag-pure-asm) -S -o $@ $<

.SECONDEXPANSION:
$(generated16_o):$$(patsubst %16.o,%16.s,$$@)
	as --32 -o $@ $<

$(name).elf:$(generated16_o)
	ld -Ttext 0 -m elf_i386 $(generated16_o) -o $(name).elf
$(name).img:$(name).elf
	objcopy -j .text -O binary $(name).elf $(name).img
clean:
	-rm $(generated16_s) $(generated16_o) $(name).s $(name).elf $(name).img 2>/dev/null
