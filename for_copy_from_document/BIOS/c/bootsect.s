	.file	"bootsect.c"
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
	pushl	$17
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$4096
	call	copy_seg
	addl	$32, %esp
	movl	$1, %eax
#APP
# 26 "bootsect.c" 1
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
	.globl	copy_seg
	.type	copy_seg, @function
copy_seg:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	16(%ebp), %edx
	movl	24(%ebp), %ecx
	movl	12(%ebp), %esi
	movl	20(%ebp), %edi
	movl	%edx, %ebx
#APP
# 38 "bootsect.c" 1
	cli 
	push %ds 
	mov %ax, %ds 
	mov %bx, %ax 
	mov %ax, %es 
	rep movsw 
	pop %ds 
	sti 
	
# 0 "" 2
#NO_APP
	movl	%ecx, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	copy_seg, .-copy_seg
	.globl	LBA_read
	.type	LBA_read, @function
LBA_read:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$16, %esp
	movl	12(%ebp), %eax
	movl	$499, %edx
#APP
# 134 "bootsect.c" 1
	out %al, %dx 
	
# 0 "" 2
#NO_APP
	sarl	$8, 12(%ebp)
	movl	12(%ebp), %eax
	movl	$500, %edx
#APP
# 134 "bootsect.c" 1
	out %al, %dx 
	
# 0 "" 2
#NO_APP
	sarl	$8, 12(%ebp)
	movl	12(%ebp), %eax
	movl	$501, %edx
#APP
# 134 "bootsect.c" 1
	out %al, %dx 
	
# 0 "" 2
#NO_APP
	movl	12(%ebp), %eax
	sarl	$8, %eax
	xorb	$-17, %al
	movl	%eax, 12(%ebp)
	movl	12(%ebp), %eax
	movl	$502, %edx
#APP
# 134 "bootsect.c" 1
	out %al, %dx 
	
# 0 "" 2
#NO_APP
	movl	$498, %edx
	movl	16(%ebp), %eax
#APP
# 136 "bootsect.c" 1
	out %al, %dx 
	
# 0 "" 2
#NO_APP
	movl	$503, %edx
	movl	$32, %eax
#APP
# 137 "bootsect.c" 1
	out %al, %dx 
	
# 0 "" 2
#NO_APP
.L8:
	movl	$503, %eax
	movl	%eax, %edx
#APP
# 138 "bootsect.c" 1
	in %dx, %al 
	
# 0 "" 2
#NO_APP
	movb	%al, -5(%ebp)
	xorb	$-120, -5(%ebp)
	cmpb	$8, -5(%ebp)
	je	.L10
	jmp	.L8
.L10:
	nop
	movl	16(%ebp), %eax
	sall	$9, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, %ecx
	movl	$496, %edx
	movl	8(%ebp), %ebx
#APP
# 139 "bootsect.c" 1
	1: 
	in %dx, %ax 
	movw (%bx), %ax 
	inc %bx 
	inc %bx 
	loop 1b 
	
# 0 "" 2
#NO_APP
	nop
	addl	$16, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	LBA_read, .-LBA_read
#APP
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
	
	_gdtm: .word 0x07FF 
		.word 0x7C00+_gdt , 0 
	
	_idtm: .word 0 
		.word 0, 0 
	
	.org 505
	_stack:
	
	.org 510
	.word 0xAA55
	
	.ident	"GCC: (GNU) 6.2.1 20160916 (Red Hat 6.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
