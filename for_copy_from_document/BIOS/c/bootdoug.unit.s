	.file	"bootdoug.unit.c"
#APP
	.code16gcc 
	.global _start
	.text
	_start:
	ljmp $0x7c0, $_here
	_here:
	cli 
	mov %cs,%ax
	mov %ax,%ds
	mov %ax,%es
	mov %ax,%ss 
	mov $_stack, %eax
	mov %eax,%esp
	#mov $0xffff,%eax 
	#mov %eax,%esp 
	#add $0x4,%esp 
	#sub $0x4,%esp 
	#pop %eax 
	pushl $0
	pushl $0
	call enter_main 
	addl $8,%esp
	#mov $0x6,%ah 
	#xor %cx,%cx 
	#mov $0x1,%dh 
	#int $0x1a 
	#you should check CF(=1 failed) 
	sti #this really works.Without this, the character even do not change.
	#int $0x8 
	#int $0x70 
	#xor %edx,%edx
	#div %edx 
	
	_die: 
	
	jmp _die 
	
#NO_APP
	.text
	.globl	enter_main
	.type	enter_main, @function
enter_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	subl	$4, %esp
	pushl	$5
	pushl	$3
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$1024
	pushl	$1984
	call	read_sector
	addl	$32, %esp
	call	enter_mid
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
# 29 "bootdoug.unit.c" 1
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
#APP
	.org 510
	
	.word 0xAA55
	
	.org 512*2
	
	 
	
	.string "now can you see me, Douglas Fulton Shaw?" 
	
	.org .+1
	
	 
	
#NO_APP
	.globl	reverse
	.type	reverse, @function
reverse:
	pushl	%ebp
	movl	%esp, %ebp
#APP
# 102 "bootdoug.unit.c" 1
	push %edx 
	push %ebx 
	movl (4+4*1)(%ebp), %ebx 
	movl (4+4*2)(%ebp), %edx 
	cmp %edx,%ebx 
	jae	2f 
	1: 
	mov (%ebx),%al 
	xchgb %al, (%edx) 
	movb %al, (%ebx) 
	inc %ebx 
	dec %edx 
	cmp %edx, %ebx 
	jb 1b 
	2: 
	pop %ebx 
	pop %edx 
	
# 0 "" 2
#NO_APP
	nop
	popl	%ebp
	ret
	.size	reverse, .-reverse
	.globl	atos
	.type	atos, @function
atos:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$16, %esp
	movl	$0, -8(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -12(%ebp)
	cmpl	$0, 8(%ebp)
	jns	.L8
	movl	$-1, -8(%ebp)
	negl	8(%ebp)
	jmp	.L8
.L9:
	movl	12(%ebp), %ebx
	leal	1(%ebx), %eax
	movl	%eax, 12(%ebp)
	movl	8(%ebp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movl	%edx, %eax
	addl	$48, %eax
	movb	%al, (%ebx)
	movl	8(%ebp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, 8(%ebp)
.L8:
	cmpl	$0, 8(%ebp)
	jg	.L9
	cmpl	$-1, -8(%ebp)
	jne	.L10
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movb	$45, (%eax)
.L10:
	movl	12(%ebp), %eax
	leal	-1(%eax), %edx
	movl	%edx, 12(%ebp)
	movb	$0, (%eax)
	pushl	12(%ebp)
	pushl	-12(%ebp)
	call	reverse
	addl	$8, %esp
	movl	12(%ebp), %edx
	movl	-12(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	-4(%ebp), %ebx
	leave
	ret
	.size	atos, .-atos
	.globl	setint
	.type	setint, @function
setint:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	8(%ebp), %ecx
	movl	12(%ebp), %edx
	movl	16(%ebp), %eax
	movb	%cl, -4(%ebp)
	movw	%dx, -8(%ebp)
	movw	%ax, -12(%ebp)
#APP
# 104 "bootdoug.unit.c" 1
	pushf 
	cli 
	push %ebx 
	push %es 
	xor %ax,%ax 
	mov %ax,%es 
	mov (4+4*1)(%ebp),%ebx 
	shl $0x2,%ebx 
	movw (4+4*2)(%ebp),%ax 
	movw %ax,%es:2(%ebx) 
	movw (4+4*3)(%ebp),%ax 
	movw %ax,%es:(%ebx) 
	pop %es 
	pop %ebx 
	popf 
	
# 0 "" 2
#NO_APP
	nop
	leave
	ret
	.size	setint, .-setint
	.globl	settimeval
	.type	settimeval, @function
settimeval:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	imulw	$1193, %ax, %ax
	movw	%ax, -2(%ebp)
	movzwl	-2(%ebp), %eax
	movl	%eax, %ecx
#APP
# 105 "bootdoug.unit.c" 1
	pushf 
	cli 
	push %eax 
	push %edx 
	movb $0x36, %al 
	movw $0x43, %dx 
	out %al, %dx 
	mov $0x40, %dx 
	mov %cl, %al 
	out %al, %dx 
	mov %ch, %al 
	out %al, %dx 
	pop %edx 
	pop %eax 
	popf 
	
# 0 "" 2
#NO_APP
	nop
	leave
	ret
	.size	settimeval, .-settimeval
	.comm	curx,4,4
	.comm	cury,4,4
	.comm	col,4,4
	.section	.rodata
.LC0:
	.string	"Loader by Douglas Fulton Shaw"
	.align 4
.LC1:
	.string	"Loading System Image.Verifying, Hold on."
.LC2:
	.string	"Now hit a key..."
.LC3:
	.string	"Input char is:"
	.align 4
.LC4:
	.string	"Welcome to X2 -- an OS designed by Douglas Fulton Shaw,2016"
.LC5:
	.string	"Setting up interrupt..."
.LC6:
	.string	">>"
	.text
	.globl	enter_mid
	.type	enter_mid, @function
enter_mid:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	call	get_screen_column
	movl	%eax, col
	movl	col, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	leal	0(,%eax,4), %edx
	addl	%edx, %eax
	subl	$12, %esp
	pushl	%eax
	call	clear_screen
	addl	$16, %esp
	movl	curx, %edx
	movl	col, %eax
	imull	%eax, %edx
	movl	cury, %eax
	addl	%edx, %eax
	subl	$4, %esp
	pushl	%eax
	pushl	$7
	pushl	$.LC0
	call	putstr
	addl	$16, %esp
	movl	%eax, cury
	movl	cury, %eax
	addl	$2, %eax
	movl	col, %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	movl	%eax, cury
	movl	curx, %eax
	addl	$1, %eax
	movl	%eax, curx
	movl	curx, %edx
	movl	col, %eax
	imull	%eax, %edx
	movl	cury, %eax
	addl	%edx, %eax
	subl	$4, %esp
	pushl	%eax
	pushl	$7
	pushl	$.LC1
	call	putstr
	addl	$16, %esp
	movl	%eax, cury
	movl	curx, %eax
	addl	$1, %eax
	movl	%eax, curx
	movl	$0, cury
	movl	curx, %edx
	movl	col, %eax
	imull	%eax, %edx
	movl	cury, %eax
	addl	%edx, %eax
	subl	$4, %esp
	pushl	%eax
	pushl	$7
	pushl	$.LC2
	call	putstr
	addl	$16, %esp
	call	getchar
	movb	%al, -9(%ebp)
	movl	curx, %eax
	addl	$1, %eax
	movl	%eax, curx
	movl	$0, cury
	movl	curx, %edx
	movl	col, %eax
	imull	%eax, %edx
	movl	cury, %eax
	addl	%edx, %eax
	subl	$4, %esp
	pushl	%eax
	pushl	$7
	pushl	$.LC3
	call	putstr
	addl	$16, %esp
	movl	col, %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	movl	%eax, cury
	movl	curx, %edx
	movl	col, %eax
	imull	%eax, %edx
	movl	cury, %eax
	addl	%eax, %edx
	movsbl	-9(%ebp), %eax
	subl	$4, %esp
	pushl	%edx
	pushl	$7
	pushl	%eax
	call	putchar
	addl	$16, %esp
	movl	curx, %eax
	addl	$1, %eax
	movl	%eax, curx
	movl	$0, cury
	movl	curx, %edx
	movl	col, %eax
	imull	%eax, %edx
	movl	cury, %eax
	addl	%edx, %eax
	subl	$4, %esp
	pushl	%eax
	pushl	$7
	pushl	$.LC4
	call	putstr
	addl	$16, %esp
	movl	curx, %eax
	addl	$1, %eax
	movl	%eax, curx
	movl	$0, cury
	movl	$25, -16(%ebp)
	subl	$8, %esp
	leal	-20(%ebp), %eax
	pushl	%eax
	pushl	-16(%ebp)
	call	atos
	addl	$16, %esp
	movl	curx, %edx
	movl	col, %eax
	imull	%eax, %edx
	movl	cury, %eax
	addl	%edx, %eax
	subl	$4, %esp
	pushl	%eax
	pushl	$7
	leal	-20(%ebp), %eax
	pushl	%eax
	call	putstr
	addl	$16, %esp
	movl	curx, %eax
	addl	$1, %eax
	movl	%eax, curx
	movl	$0, cury
	movl	curx, %edx
	movl	col, %eax
	imull	%eax, %edx
	movl	cury, %eax
	addl	%edx, %eax
	subl	$4, %esp
	pushl	%eax
	pushl	$7
	pushl	$.LC5
	call	putstr
	addl	$16, %esp
	movl	$new_int13, %eax
	cwtl
	subl	$4, %esp
	pushl	%eax
	pushl	$1984
	pushl	$13
	call	setint
	addl	$16, %esp
	movl	$new_int12, %eax
	cwtl
	subl	$4, %esp
	pushl	%eax
	pushl	$1984
	pushl	$12
	call	setint
	addl	$16, %esp
	subl	$12, %esp
	pushl	$100
	call	settimeval
	addl	$16, %esp
	movl	$putter, %eax
	cwtl
	subl	$4, %esp
	pushl	%eax
	pushl	$1984
	pushl	$8
	call	setint
	addl	$16, %esp
	movl	curx, %eax
	addl	$1, %eax
	movl	%eax, curx
	movl	$0, cury
	movl	curx, %edx
	movl	col, %eax
	imull	%eax, %edx
	movl	cury, %eax
	addl	%edx, %eax
	subl	$4, %esp
	pushl	%eax
	pushl	$7
	pushl	$.LC6
	call	putstr
	addl	$16, %esp
	movl	col, %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	movl	%eax, cury
	nop
	leave
	ret
	.size	enter_mid, .-enter_mid
	.globl	flag
	.bss
	.align 4
	.type	flag, @object
	.size	flag, 4
flag:
	.zero	4
	.text
	.globl	putter
	.type	putter, @function
putter:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
#APP
# 192 "bootdoug.unit.c" 1
	cli 
	mov $0x20, %al 
	out %al, $0x20 
	#mov (2*2+4)(%ebp),%ax
	#or $0x0200, %ax 
	#mov %ax,(2*2+4)(%ebp) 
	
# 0 "" 2
#NO_APP
	movl	curx, %edx
	movl	col, %eax
	imull	%eax, %edx
	movl	cury, %eax
	addl	%edx, %eax
	movl	%eax, -12(%ebp)
	movl	flag, %eax
	testl	%eax, %eax
	jne	.L16
	movl	$1, flag
	subl	$4, %esp
	pushl	-12(%ebp)
	pushl	$7
	pushl	$95
	call	putchar
	addl	$16, %esp
	jmp	.L17
.L16:
	movl	flag, %eax
	cmpl	$1, %eax
	jne	.L18
	movl	$2, flag
	subl	$4, %esp
	pushl	-12(%ebp)
	pushl	$7
	pushl	$92
	call	putchar
	addl	$16, %esp
	jmp	.L17
.L18:
	movl	flag, %eax
	cmpl	$2, %eax
	jne	.L19
	movl	$3, flag
	subl	$4, %esp
	pushl	-12(%ebp)
	pushl	$7
	pushl	$124
	call	putchar
	addl	$16, %esp
	jmp	.L17
.L19:
	movl	flag, %eax
	cmpl	$3, %eax
	jne	.L17
	movl	$0, flag
	subl	$4, %esp
	pushl	-12(%ebp)
	pushl	$7
	pushl	$47
	call	putchar
	addl	$16, %esp
.L17:
#APP
# 205 "bootdoug.unit.c" 1
	leave 
	sti 
	iretw 
	
# 0 "" 2
#NO_APP
	nop
	leave
	ret
	.size	putter, .-putter
	.section	.rodata
.LC7:
	.string	"int 13"
	.text
	.globl	new_int13
	.type	new_int13, @function
new_int13:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
#APP
# 217 "bootdoug.unit.c" 1
	cli 
	
# 0 "" 2
#NO_APP
	subl	$4, %esp
	pushl	$2
	pushl	$7
	pushl	$.LC7
	call	putstr
	addl	$16, %esp
#APP
# 221 "bootdoug.unit.c" 1
	leave 
	iretw 
	
# 0 "" 2
#NO_APP
	nop
	leave
	ret
	.size	new_int13, .-new_int13
	.section	.rodata
.LC8:
	.string	"int 12"
	.text
	.globl	new_int12
	.type	new_int12, @function
new_int12:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
#APP
# 229 "bootdoug.unit.c" 1
	cli 
	
# 0 "" 2
#NO_APP
	subl	$4, %esp
	pushl	$2
	pushl	$7
	pushl	$.LC8
	call	putstr
	addl	$16, %esp
#APP
# 233 "bootdoug.unit.c" 1
	leave 
	iretw 
	
# 0 "" 2
#NO_APP
	nop
	leave
	ret
	.size	new_int12, .-new_int12
	.globl	peekchar
	.type	peekchar, @function
peekchar:
	pushl	%ebp
	movl	%esp, %ebp
#APP
# 245 "bootdoug.unit.c" 1
	mov $0x11, %ah 
	int $0x16	
	jz 1f		
	1: 
	xor %ax,%ax
	
# 0 "" 2
#NO_APP
	nop
	popl	%ebp
	ret
	.size	peekchar, .-peekchar
	.globl	getchar
	.type	getchar, @function
getchar:
	pushl	%ebp
	movl	%esp, %ebp
#APP
# 258 "bootdoug.unit.c" 1
	mov $0x10, %ah 
	int $0x16	
	
# 0 "" 2
#NO_APP
	nop
	popl	%ebp
	ret
	.size	getchar, .-getchar
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
# 274 "bootdoug.unit.c" 1
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
# 299 "bootdoug.unit.c" 1
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
	jmp	.L28
.L29:
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
.L28:
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L29
	movl	-4(%ebp), %eax
	leave
	ret
	.size	putstr, .-putstr
	.globl	clear_screen
	.type	clear_screen, @function
clear_screen:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, -4(%ebp)
	jmp	.L32
.L33:
	pushl	-4(%ebp)
	pushl	$0
	pushl	$0
	call	putchar
	addl	$12, %esp
	addl	$1, -4(%ebp)
.L32:
	movl	-4(%ebp), %eax
	cmpl	8(%ebp), %eax
	jl	.L33
	nop
	leave
	ret
	.size	clear_screen, .-clear_screen
	.globl	get_screen_column
	.type	get_screen_column, @function
get_screen_column:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$16, %esp
	movl	$64, %eax
	movl	$74, %edx
	movl	%edx, %ebx
#APP
# 341 "bootdoug.unit.c" 1
	push %edx 
	push %ebx 
	push %es 
	mov %ax,%es 
	movl %es:(%ebx),%eax 
	pop %es 
	pop %ebx 
	pop %edx 
	
# 0 "" 2
#NO_APP
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movzwl	%ax, %eax
	addl	%eax, %eax
	addl	$16, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	get_screen_column, .-get_screen_column
#APP
	.global _idtm 
	
	.global _gdtm 
	
	.global _gdt 
	
	.global _stack 
	
	.set _stack, 512*2 
	
	.ident	"GCC: (GNU) 6.2.1 20160916 (Red Hat 6.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
