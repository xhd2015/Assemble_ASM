	.file	"just.c"
#APP
	.code16gcc

	.global _start
	.text
	_start:
	ljmp $0x7c0,$here
	here:
	mov %cs,%ax
	mov %ax,%ds
	mov %ax,%es
	mov $stack,%eax
	mov %eax,%esp
	pushl $0
	pushl $0
	calll main
	addl $8,%esp
	die:
	jmp die
	
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
	subl	$20, %esp
	movl	$0, -12(%ebp)
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -12(%ebp)
	subl	$8, %esp
	pushl	%eax
	pushl	$88
	call	write_video_ram
	addl	$16, %esp
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -12(%ebp)
	subl	$8, %esp
	pushl	%eax
	pushl	$88
	call	write_video_ram
	addl	$16, %esp
	movl	$0, -16(%ebp)
	jmp	.L2
.L3:
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -12(%ebp)
	subl	$8, %esp
	pushl	%eax
	pushl	$88
	call	write_video_ram
	addl	$16, %esp
	addl	$1, -16(%ebp)
.L2:
	cmpl	$999, -16(%ebp)
	jle	.L3
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	leave
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.globl	write_video_ram
	.type	write_video_ram, @function
write_video_ram:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movb	%al, -8(%ebp)
	movl	$47104, %eax
	movzbl	-8(%ebp), %edx
	movl	12(%ebp), %ebx
	movl	%edx, %ecx
#APP
# 42 "just.c" 1
	pushw %es
	mov %ax,%es
	movb %cl,%es:0(,%ebx,2)
	popw %es
	
# 0 "" 2
#NO_APP
	nop
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	write_video_ram, .-write_video_ram
#APP
	.org 505
	stack:
	
	.org 510
	.word 0xAA55
	
	.ident	"GCC: (GNU) 6.2.1 20160916 (Red Hat 6.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
