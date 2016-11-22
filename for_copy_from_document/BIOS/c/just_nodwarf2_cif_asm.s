	.file	"just.c"
/*
This kind of asm file,does not contain .cfi_** directives
Then it is just fine to run 'as' without option 'as --32'
*/
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
	leal	4(%esp), %ecx
.LCFI0:
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
.LCFI1:
	movl	%esp, %ebp
	pushl	%ecx
.LCFI2:
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
.LCFI3:
	leave
.LCFI4:
	leal	-4(%ecx), %esp
.LCFI5:
	ret
.LFE0:
	.size	main, .-main
	.globl	write_video_ram
	.type	write_video_ram, @function
write_video_ram:
.LFB1:
	pushl	%ebp
.LCFI6:
	movl	%esp, %ebp
.LCFI7:
	pushl	%ebx
	subl	$4, %esp
.LCFI8:
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
.LCFI9:
	popl	%ebp
.LCFI10:
	ret
.LFE1:
	.size	write_video_ram, .-write_video_ram
#APP
	.org 505
	stack:
	
	.org 510
	.word 0xAA55
	
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0
	.byte	0x3
	.string	""
	.uleb128 0x1
	.sleb128 -4
	.uleb128 0x8
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x88
	.uleb128 0x1
	.align 4
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB0
	.long	.LFE0-.LFB0
	.byte	0x4
	.long	.LCFI0-.LFB0
	.byte	0xc
	.uleb128 0x1
	.uleb128 0
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0x10
	.byte	0x5
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.byte	0x4
	.long	.LCFI2-.LCFI1
	.byte	0xf
	.uleb128 0x3
	.byte	0x75
	.sleb128 -4
	.byte	0x6
	.byte	0x4
	.long	.LCFI3-.LCFI2
	.byte	0xc
	.uleb128 0x1
	.uleb128 0
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xc5
	.byte	0x4
	.long	.LCFI5-.LCFI4
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.align 4
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB1
	.long	.LFE1-.LFB1
	.byte	0x4
	.long	.LCFI6-.LFB1
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI8-.LCFI7
	.byte	0x83
	.uleb128 0x3
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xc3
	.byte	0x4
	.long	.LCFI10-.LCFI9
	.byte	0xc5
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.align 4
.LEFDE3:
	.ident	"GCC: (GNU) 6.2.1 20160916 (Red Hat 6.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
