	.file	"memcopy.c"
	.text
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
# 10 "memcopy.c" 1
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
	.size	memcopy, .-memcopy
	.ident	"GCC: (GNU) 6.2.1 20160916 (Red Hat 6.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
