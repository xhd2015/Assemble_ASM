
name := bootsect
suffix := c o elf img
ccflag-pure-asm := -fno-asynchronous-unwind-tables
ccflag-asm-default := -m32 -S

.PHONY: view_codes see_doc help
help:
	@echo "you can pass opt to make,like make Target opt=?.\
	The avaible opt are opt=[pure-asm],opt=pure-asm will generate\
	a pure assemble code from c codes,without any extra information(say,debug information and unwind tables)."
see_doc:
	@
	cat a_summ*

view_codes:$(name).img
	@
	objdump -D -m i8086 -b binary $(name).img
.ONESHELL:
$(name).s:$(name).c
	opt=$(opt)
	ccflags="$(ccflag-asm-default)"
	if [ ''$$opt = pure-asm ];then
		ccflags="$$ccflags"' '"$(ccflag-pure-asm)"
	fi
	gcc $$ccflags $(name).c -o $(name).s

$(name).o:$(name).s
	as --32 $(name).s -o $(name).o

$(name).elf:$(name).o
	ld -Ttext 0 -m elf_i386 $(name).o -o $(name).elf
$(name).img:$(name).elf
	objcopy -j .text -O binary $(name).elf $(name).img

