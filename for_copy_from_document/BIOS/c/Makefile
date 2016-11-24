
name := bootdoug
#the support file is in a specific order
support := $(name)_head int13 $(name)_mid int16 memcopy putchar bda $(name)_tail
suffix := c o elf img
ccflag-pure-asm := -fno-asynchronous-unwind-tables
ccflag-asm-default := -m32 -S

generated16_o := $(patsubst %,%16.o,$(support))
generated16_s := $(patsubst %,%16.s,$(support))
generated_c := $(patsubst %,%.c,$(support))

.PHONY: view_codes see_doc help include_once clean
.ONESHELL:
help:
	@
	echo "@depreciated opt=pure-asm is supported no longer."
	echo "==============================================="
	echo "you can pass opt to make,like make Target opt=?.\
	The avaible opt are opt=[pure-asm],opt=pure-asm will generate\
	a pure assemble code from c codes,without any extra information(say,debug information and unwind tables)."
	echo "make include_once file=?	==> generate the include once declarement"
	echo "make view_codes file=? 	==> view binary file codes"
see_doc:
	@
	cat a_summ*
.ONESHELL:
view_codes:
	@
	file=$(file)
	file=$${file:=$(name).img}
	objdump -D -m i8086 -b binary $${file}
.ONESHELL:
include_once:
	@	
	orifile=$(file)
	file=$${orifile:?missing option file=?}	
	if [ -f $$orifile ];then
		echo "file already exist,no overriding it"
		exit
	fi
	file=$${file%.*}
	file=$$(python3 -c "x='$${file}';x=x.upper().replace('.','_');print(x)")
	file=__$${file}_H__
	echo "//=========FILE: $${orifile}======" > $$orifile
	echo "#ifndef $${file} /*START this file,define once*/" >>$$orifile
	echo "#define $${file}" >>$$orifile
	echo	>> $$orifile
	echo "#endif /*END this file*/" >>$$orifile


.ONESHELL:
$(name).unit.c:$(generated_c)
	echo "" > $(name).unit.c
	for i in $(generated_c);do
		cat $$i >> $(name).unit.c
	done

$(name).unit.s:$(name).unit.c
	gcc -m32 $(ccflag-pure-asm) -S -o $@ $<
.ONESHELL:
$(name).s:$(generated16_s)
	echo "generating $(name).s..."
	for i in $(generated16_s);do
		echo "processing $$i..."
		cat $$i|sed "/\s*\.code16gcc/d"|sed "/\s*\.file/d"|sed "/\s*\.ident[^G]*G/d"|sed "/\s*\.section\s*\.note/d" >temp
		cat temp > $$i
	done
	(echo -e "\t.code16gcc\n\t.file\t\"$(name).s\"\n";cat $(generated16_s)) > $(name).s

$(name).unit.elf:$(name).unit.o
	ld -Ttext 0 -m elf_i386 $< -o $@

$(name).unit.o:$(name).unit.s
	as --32 -o $@ $<
$(name).unit.img:$(name).unit.elf
	objcopy -j .text -j .rodata -j .data -O binary $< $@

.ONESHELL:
.SECONDEXPANSION:
$(generated16_s):$$(patsubst %16.s,%.c,$$@)
	echo 'Generating $@...'
	@gcc -m32 $(ccflag-pure-asm) -S -o $@ $<
	(echo "	.code16gcc";cat $@) > temp
	cat temp > $@

.SECONDEXPANSION:
$(generated16_o):$$(patsubst %16.o,%16.s,$$@)
	as --32 -o $@ $<

$(name).elf:$(generated16_o)
	ld -Ttext 0 -m elf_i386 $(generated16_o) -o $(name).elf
$(name).img:$(name).elf
	objcopy -j .text -j .rodata -j .data -O binary $(name).elf $(name).img
clean:
	-rm temp
	-rm $(generated16_s)
	-rm $(generated16_o) 
	-rm $(name).s $(name).elf $(name).img 
	-rm $(name).unit.*
