	.file	"bootdoug.unit.c"
#APP
	.code16gcc 
	.global _start
	.text
	_start:
	ljmp $0x7c0, $_here
	_here:
	mov %cs,%ax
	mov %ax,%ds
	mov %ax,%es
	mov %ax,%ss 
	mov $_stack, %eax
	mov %eax,%esp
	pushl $0
	pushl $0
	call enter_main 
	addl $8,%esp
	
	_die: 
	
	jmp _die 
	
	.section	.rodata
.LC0:
	.string	"Loader by Douglas Fulton Shaw"
	.align 4
.LC1:
	.string	"Loading System Image.Verifying, Hold on."
#NO_APP
	.text
	.globl	enter_main
	.type	enter_main, @function
enter_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	subl	$4, %esp
	pushl	$1
	pushl	$2
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$512
	pushl	$1984
	call	read_sector
	addl	$32, %esp
	subl	$4, %esp
	pushl	$0
	pushl	$7
	pushl	$.LC0
	call	putstr
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	addl	$1, -12(%ebp)
	addl	$1, -12(%ebp)
	subl	$4, %esp
	pushl	-12(%ebp)
	pushl	$7
	pushl	$.LC1
	call	putstr
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	subl	$12, %esp
	pushl	$512
	pushl	$0
	pushl	$0
	pushl	$512
	pushl	$1984
	call	memcopy
	addl	$32, %esp
	movl	$0, %eax
	leave
	ret
	.size	enter_main, .-enter_main
	.globl	read_sector
	.type	read_sector, @function
read_sector:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$40, %esp
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
	movl	32(%ebp), %esi
	movl	%esi, -48(%ebp)
	movb	%al, -28(%ebp)
	movb	%bl, -32(%ebp)
	movw	%cx, -36(%ebp)
	movb	%dl, -40(%ebp)
	movzbl	-48(%ebp), %eax
	movb	%al, -44(%ebp)
#APP
# 33 "bootdoug.unit.c" 1
	push %es 
	push %ebx 
	push %edx 
	push %ecx 
	mov (4+4*1)(%ebp), %eax 
	mov %ax, %es 
	mov (4+4*2)(%ebp), %ebx 
	mov (4+4*3)(%ebp), %dl 
	mov (4+4*4)(%ebp), %dh 
	mov (4+4*5)(%ebp), %ax 
	mov %al, %ch 
	mov (4+4*6)(%ebp), %cl 
	and $0x03, %ah 
	and $0xCF, %cl 
	or  %ah, %cl
	mov $0x02, %ah 
	mov (4+4*7)(%ebp), %al 
	int $0x13 
	pop %ecx 
	pop %edx 
	pop %ebx 
	pop %es 
	
# 0 "" 2
#NO_APP
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	sarl	$8, %eax
	addl	$40, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	read_sector, .-read_sector
	.globl	memcopy
	.type	memcopy, @function
memcopy:
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
# 87 "bootdoug.unit.c" 1
	cli 
	push %es 
	push %ds 
	mov %ax, %ds 
	mov %bx, %ax 
	mov %ax, %es 
	rep movsb 
	pop %ds 
	pop %es 
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
	.size	memcopy, .-memcopy
#APP
	.set logical_zero, 0 
	
	.org 510 - logical_zero
	
	.word 0xAA55
	
	.string "now can you see me, Douglas Fulton Shaw?" 
	
	.org .+1
	
	 
	
#NO_APP
	.globl	putchar
	.type	putchar, @function
putchar:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$8, %esp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movb	%dl, -8(%ebp)
	movb	%al, -12(%ebp)
#APP
# 125 "bootdoug.unit.c" 1
	push %es 
	mov 8(%ebp),%cl 
	mov 12(%ebp),%ch 
	mov 16(%ebp),%ebx 
	mov $0xb800, %ax 
	mov %ax, %es 
	movw %cx, %es:(%ebx) 
	mov %ebx,%eax 
	inc %eax 
	inc %eax 
	pop %es 
	
# 0 "" 2
#NO_APP
	nop
	addl	$8, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	putchar, .-putchar
	.globl	putstr
	.type	putstr, @function
putstr:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	12(%ebp), %eax
	movb	%al, -20(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, -4(%ebp)
	jmp	.L9
.L10:
	movsbl	-20(%ebp), %edx
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	pushl	-4(%ebp)
	pushl	%edx
	pushl	%eax
	call	putchar
	addl	$12, %esp
	movl	%eax, -4(%ebp)
	addl	$1, 8(%ebp)
.L9:
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L10
	movl	-4(%ebp), %eax
	leave
	ret
	.size	putstr, .-putstr
#APP
	.set logical_zero, 0 
	
	.global _idtm 
	
	.global _gdtm 
	
	.global _gdt 
	
	.global _stack 
	
	.org 512*2-100-logical_zero
	
	.word 0xAA55
	
	.set _stack, 512*3 
	
	.ident	"GCC: (GNU) 6.2.1 20160916 (Red Hat 6.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
