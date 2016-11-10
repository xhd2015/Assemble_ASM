	.code16
	.global _start
	.text
	
_start:
	movw %cs,%ax
	movw %ax,%ds /*set ds=cs */
	movw %ax,%ss /*set ss=cs */

	movw $stack,%ax
	movw %ax,%sp	/* set sp */
	#====== Init Done !!! =====

	pushw $length
	pushw $message
#	callw $display_str /* invalid */
	callw display_str
	
	
	
	#=== Return to dos
	movw $0x4c00,%ax
	int $0x21
message:	.string "Hello , world!\n\0"
length = . - message
display_str:
	pushw %bp
	movw 4(%esp),%ax /* str */
	/* pay attention to this ,
	the stack is like this:
		6[ len_low ]
		5[ len_high ]
		4[ straddr_low]
		3[ straddr_high]
		2[ bp_low ]
		1[ bp_high ]
	esp---> 0[]
	this means it has a little difference with the model we discussed yesterday.In that model,esp always point to an existing content,substraction happens before everything
	but here,substraction happens after everything.What causes confusion that in both models , the content of (%esp) always denotes to the current point.This means you can't use 0(%esp) in this mode,cause it is undefined yet.
	pay attention to this but let it go.


	*/
	movw %ax,%bp
	movw 6(%esp),%cx /* length */
	movw $0x1301,%ax
	movw $0x000c,%bx
	movb $0x0,%dl
	int $0x10
	popw %bp
	ret
	.org 0x100
stack:	/* the buttom of the stack */

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
