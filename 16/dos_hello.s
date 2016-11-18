	.code16
	.arch i8086,nojumps
	.global _start
	.text
	jmp _start
some_thing_before_start:	.word 0x8877
_start:
	mov %cs,%ax
	mov %ax,%ds /*set ds=cs */
	mov %ax,%ss /*set ss=cs */

	mov $stack,%ax
	mov %ax,%sp	/* set sp */
	#====== Init Done !!! =====


	mov $length,%ax
	push %ax
	mov $message,%ax
	push %ax
	call display_str
	add 4,%sp
	
	
	#=== Return to dos
	mov $0x4c00,%ax
	int $0x21
message:	.string "Hello , world!\n\0"
length = . - message
display_str:
	push %bp
	mov %sp,%bp
	mov 4(%bp),%ax /* str */
	/* pay attention to this ,
	the stack is like this:
		8[ len_high ]
		7[ len_low ]
		6[ straddr_high]
		5[ straddr_low]
		4[ rtn_ip_high ]
		3[ rtn_ip_low ]
		2[ bp_high ]
	sp--->	1[ bp_low ]
	*/
	#call argument: 0x10 ( ax=num,bx=pre,cx=arg1,bp=base addr)
	mov 6(%bp),%cx /* length */
	push %bp
	mov %ax,%bp
	mov $0x1301,%ax
	mov $0x000c,%bx
	mov $0x0,%dl

	int $0x10

	pop %bp
	mov %bp,%sp
	pop %bp
	ret

	/* additional
	as -32   <=== as
	ld -Ttext 0x100 -m elf_i386 <=== ld
	objcopy -j .text -O binary $ELF COMFILE <===== cut .text into binary file
	objdump -d -m i8086 <=== objdump -dx
	readelf -S $ELF	<===== view headers
	objdump -D -b binary -m i8086 $COM  <==== to see .com file's disassemble

	*/
	/* Additional -- get help from community
	http : //www.linux.org/groups
	*/
	.org 0x100
stack:	/* the buttom of the stack */
	
