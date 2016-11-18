
name := just
suffix := c o elf img

.PHONY: view_codes see_doc

see_doc:
	@
	cat a_summ*

view_codes:$(name).img
	@
	objdump -D -m i8086 -b binary $(name).img

$(name).s:$(name).c
	gcc -S -m32 $(name).c -o $(name).s

$(name).o:$(name).s
	as --32 $(name).s -o $(name).o

$(name).elf:$(name).o
	ld -Ttext 0 -m elf_i386 $(name).o -o $(name).elf
$(name).img:$(name).elf
	objcopy -j .text -O binary $(name).elf $(name).img

