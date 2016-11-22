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
.LFB0:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
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
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	write_video_ram
	.type	write_video_ram, @function
write_video_ram:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$4, %esp
	.cfi_offset 3, -12
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
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	write_video_ram, .-write_video_ram
#APP
	.org 505
	stack:
	
	.org 510
	.word 0xAA55
	
	.ident	"GCC: (GNU) 6.2.1 20160916 (Red Hat 6.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
