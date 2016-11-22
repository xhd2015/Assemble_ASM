	.file	"just.c"
	.code16gcc  
	#difference from .code16 is that,it treate all jmp,call,ret as 32-bit
	#if you want a pure i8086 assemble,don't use .code16gcc
	#but can you still write in c?
	#Well,this is worth to think.
	#
	.text
	.globl	main,_start
	.type	main, @function
_start:
main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$0, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 6.2.1 20160916 (Red Hat 6.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
