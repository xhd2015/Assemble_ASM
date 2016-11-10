#hello.s
	.data
msg:	.string "Hello World !\n"
	len =	. -msg

	.text
	.global _start  #entry

_start:
	movl $len,%edx
	movl $msg,%ecx
	movl $1,%ebx
	movl $4,%eax
	int $0x80

	movl $0,%ebx
	lj
	movl $1,%eax
	int $0x80
	
