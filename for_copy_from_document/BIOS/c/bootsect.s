	.file	"bootsect_head.c"
#APP
	.code16gcc
	
	.global _start
	.text
	_start:
	ljmp $0x7c0,$_here
	_here:
	mov %cs,%ax
	mov %ax,%ds
	mov %ax,%es
	mov $_stack,%eax
	mov %eax,%esp
	pushl $0
	pushl $0
	call main
	addl $8,%esp
	_die:
	jmp _die
	
#NO_APP
	.text
	.globl	main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$4, %esp
	subl	$4, %esp
	pushl	$17
	pushl	$0
	pushl	$4096
	call	LBA_read
	addl	$16, %esp
	subl	$12, %esp
	pushl	$8192
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$4096
	call	memcopy
	addl	$32, %esp
	movl	$1, %eax
#APP
# 31 "bootsect_head.c" 1
	lidt	_idtm 
	lgdt	_gdtm 
	lmsw   %ax 
	ljmp   $0x8, $0x0 
	
# 0 "" 2
#NO_APP
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	leave
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 6.2.1 20160916 (Red Hat 6.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
	.file	"bootsect_tail.c"
#APP
	.global _stack 
	
	.global _idtm 
	
	.global _gdtm 
	
	.global _gdt 
	
	 
	_logical_zero_pos:
	 
	
	_gdt:
	.word 0,0,0,0 
	.word 0x07FF 
	.word 0x0000 
	.word 0x9A00 
	.word 0x00C0 
	.word 0x07FF 
	.word 0x0000 
	.word 0x9200 
	.word 0x00C0 
	
	 
	_gdtm:
	.word 0x07FF
	
	 
	
	.long _gdt+0x7c00
	
	 
	_idtm:
	.word 0
	
	 
	
	.long 0
	
	 
	
	.long _logical_zero_pos
	
	last_len = 378 
	
	.org 505-last_len
	_stack:
	 
	
	.org 510-last_len
	
	.word 0xAA55
	
	.ident	"GCC: (GNU) 6.2.1 20160916 (Red Hat 6.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
