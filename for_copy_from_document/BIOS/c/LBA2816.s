	.file	"LBA28.c"
	.text
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
# 12 "LBA28.c" 1
	out %al, %dx 
	
# 0 "" 2
#NO_APP
	sarl	$8, 12(%ebp)
	movl	12(%ebp), %eax
	movl	$500, %edx
#APP
# 12 "LBA28.c" 1
	out %al, %dx 
	
# 0 "" 2
#NO_APP
	sarl	$8, 12(%ebp)
	movl	12(%ebp), %eax
	movl	$501, %edx
#APP
# 12 "LBA28.c" 1
	out %al, %dx 
	
# 0 "" 2
#NO_APP
	movl	12(%ebp), %eax
	sarl	$8, %eax
	andl	$239, %eax
	movl	%eax, 12(%ebp)
	movl	12(%ebp), %eax
	movl	$502, %edx
#APP
# 12 "LBA28.c" 1
	out %al, %dx 
	
# 0 "" 2
#NO_APP
	movl	$498, %edx
	movl	16(%ebp), %eax
#APP
# 13 "LBA28.c" 1
	out %al, %dx 
	
# 0 "" 2
#NO_APP
	movl	$503, %edx
	movl	$32, %eax
#APP
# 14 "LBA28.c" 1
	out %al, %dx 
	
# 0 "" 2
#NO_APP
.L4:
	movl	$503, %eax
	movl	%eax, %edx
#APP
# 15 "LBA28.c" 1
	in %dx, %al 
	
# 0 "" 2
#NO_APP
	movb	%al, -5(%ebp)
	andb	$-120, -5(%ebp)
	cmpb	$8, -5(%ebp)
	je	.L6
	jmp	.L4
.L6:
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
# 16 "LBA28.c" 1
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
	.ident	"GCC: (GNU) 6.2.1 20160916 (Red Hat 6.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
