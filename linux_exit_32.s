
	.code64 #.code32 ==> this will confine to not use rsp
	#for all uses,an advance:
	#	do not mix '.code32' with 'as --64'
	# 	use '.code32' with 'as --32' and '.code64' with 'as --64' correspondingly

	#some differences in 64	<=== 32:
	#	pop,push <=== pushl popl 
	#	rsp,rbp <===== ebp,esp
	#		otherwise , just the low 4-byte is pushed
	/*
	new design:
		.ascii
			like "Hello world\0"
			\ is available, \0 is NOT automatically added
		.byte
		.int	==>short
		.long    ==> in 64, it's 4-byte
	no jb,but jg

	*/
	.section .data
arr:	.long 5,4,9,3,0
msg:	.ascii "Hello Wolrd\n.\0"
len 	= . - msg
exit_message:	.ascii "exiting now.\0"
message_len = .- exit_message
	.section .text
	.global _start
_start:
	/*
	mov %cs,%ax
	pushw %ax
	call change_ds
	add $2,%rsp
	*/
	push $arr #8-byte
	call find_max
#	addl $8,%esp  # in 32 , use pop instead. each pushl is 8
	#	popl!=addl , because 8-byte adding operation makes 0x7fffff4e28 by adding $0x8 into 0xffff4e28,0x7fff had disappeared
	add $8,%rsp

	#use ds to locate _start
	#_start 68 22 01 60 00
	movl %ds:_start,%eax
	movl %cs:_start,%ebx
	#RESULT : eax=ebx

	#	pushw $0x3b #cause cs=0x33,index is 0x110,0x3b index is 0x111---- this is failed,because when loading segment,the target segment must exist.
	pushw $0x2b #cause ss=0x2b,set it,only if it is different with cs
	call change_ds
	add	$2,%rsp
	#set an invalid descriptor for ds,see if ds will redirect to cs
	movl %ds:_start,%eax
	#===RESULT the same.This indicates ss.base=cs.base

	#===TEST : through cs,get the current stack
	mov $0x1111222233334444,%rax
	push %rax
	mov %rsp,%rbx
	mov %cs:(%rbx),%rcx
	#RESULT : rcx=(rsp)


	#set ss=0,will it act like the ds by just using cs?
	/*
	movw $0,%ax
	movw %ax,%ss
	mov %ss:(%rsp),%rdx
	*/
	#RESULT : falied,you can't set ss=0

	#set ss=0x33-->cs
	/*
	movw $0x33,%ax
	movw %ax,%ss
	mov %ss:(%rsp),%rdx
	*/
	#RESULT : falied to set ss=0x33 , cause CPL check.

	#===TEST :show message
	push $len
	push $msg
	call int_80_print
	add $16,%rsp
	#===RESULT : worked,showed message

	#===TEST ret_jmp: use push+ret to mock a jmp
	#set cs=ss
	#	ljmp $0xfebc, $0x12345678 -- can't ljmp. is unsupported
	pushw $0
	pushw $0
	mov $in_here,%eax
	movw %ax,%bx
	shr $16,%eax
	pushw %ax
	pushw %bx

	ret
	#===RESULT ret_jmp:
	#	not the same with lret_ljmp, ret will pop 8-byte into rip,the whole 8-byte is considered to be the rip's value
	#	jmp has some differences with ljmp
	#		jmp can move in a space from 0 ~ 64-bit in a segment
	#	while
	#		ljmp can only move in a space from 0 ~ 32 bit in a segment
	# pay attention to that,the space refered above is all virtual spaces in a process's segment.
	# also pay attention,
	#	cs will change nothing
	# so exactly, ret will do like this:
	#	ret =
	#		pop rip(8-byte)
	# again,note the difference with that in lret.
	
	#===RESULT : worked.The info "exiting now." printed

	# several problems:
	#	1.how to set CS,IP
	#	2.use ret,lret to mock jmp,ljmp
	#ret is just simplely pop the stack
in_here:
	#mov to cs will cause SIGKILL
	#still running fine will indicate that cs.base=ss.base and cs.PL>=ss.PL

	
	#The Whole test shows that, a segment descriptor may have the same base address , but have different privilage level

	#===TEST :use push+lret to mock ljmp,or to mock set %cs
	movw %cs,%ax
	pushw $0
	pushw %ax
	/*
	[]*n
	[]*m
	m=8
		n=8 not working
		n=4 not working
		n=2 not working
		n=12 not working
	m=4
		n=4 ===>working
	*/
	movl $last_part,%eax
	movw %ax,%bx
	shr $16,%eax
	pushw %ax
	pushw %bx
	jmp set_csip
	#===RESULT : if set cs<===ss,then SIGSEGV is raised
	#		if set cs===>ss,the same thing goes happening
	#		but use cs-->ss,use cs<---ss are all fine
	#===RESULT 2:
	#	lcall new_cs,new_ip= (exactly,check the stack,you will know it)
	#		pushl old_cs(4-byte)
	#		pushl old_ip(4-byte)
	#		cs=new_cs
	#		ip=new_id
	#	lret	=
	#		pop 4-byte into 8-byte rip
	#		pop 4-byte into 2-byte cs
	#so concludingly,we can say lcall has a limitation that it's offset shall be no bigger than 4GB(2^32 Byte),no matter what the capacity of ram is
	# p.s ram capacity=2^addr_width_in_use * 8 bit
	# say , my computer addr_width_in_use=32,word_length=64
	#	capacity=4G*8 bit=4G*Byte=4GB
	# word_length cannot affect the bus, it is none bussiness with the actual capacity
	#	with addr_width_in_use=32 , the rip will just act like eip.Don't think that the higher 32 bit of rip will be used
last_part:	
	movl $0,%ebx
	call exit_proc
	# void int_80_print(str,len)
int_80_print:
	enter $0,$0
	movl $0x4,%eax
	movl $1,%ebx
	movl 16(%rbp),%ecx
	movl 24(%rbp),%edx
	int $0x80
	leave
	ret
	#void set_ip   ---- use jmp instead of call
set_ip:	
	ret
	#void set_csip  ---- use jmp instead of call
set_csip:
	lret
	
	# void exit_proc(ebx)
exit_proc:
	push $message_len
	push $exit_message
	call int_80_print
	add $16,%rsp
	
	movl $1,%eax
	int $0x80
	/*
	.global means don't discard symbols after compiling,cause ld will use it.
	and _start is a predefined symbol for ld to load address for cs.
	0x80
		void 1=exit(ebx)
			exit is a quick way to kill the process.Actually,exit is so speciall that even it has a return value,that value will never be catch.
			after this , echo $? will find the return code
	*/

	# int find_max(addr)
	# .stdcall c
find_max:
	/*
	push %rbp
	mov %rsp,%rbp
	*/
	enter $0,$0
	#the reason using ebp is that,esp will always change ,thus it is never sure where the arguments are.If ebp is always the hidden argument for a call,it can always be used to locate the arguments
	
	#example:
	#	movl 4(%esp),%esi
	#	movl (%esp),%esi  #===> esp-->last_ip
	#	last_ip is 8-byte long in --64 option
	#		thus should use 8(%esp) to get the first argument
	movl 16(%rbp),%esi
	movl %cs:(%esi),%eax
	addl $4,%esi
	#addq is 64-bit
	pushw %ax
	movw $0,%ax
	mov %ax,%ds
	popw %ax
local_here:
	movl %ds:(%esi),%ebx
	#finally we understand this,if we set ds as 0, then any ds prefix will be relocated to cs
	#because actually the data can be accessed by use %cs:
	#we can use ds to locate a data in cs , as if we're using cs
	testl %ebx,%ebx
	jz	local_end
	cmpl %eax,%ebx
	jbe 	local_noupdate
	movl %ebx,%eax
local_noupdate:
	addl $4,%esi
	jmp local_here
local_end:
#	mov %rbp,%rsp
#	pop %rbp
	#equal to 'enter,and leave'
	leave
	/*
	[]*8  arg1
	[]*8  last_ip
	[]*8  last_ebp  <--- rbp
	
	*/
	ret

	# int find_max_perfect(addr)
find_max_perfect:	
	ret
	# void change_ds(seg_descriptor)
	# as the 80386 manual pointed out , a loading to ss,ds,cs,xs in protected mode will result in some extra actions,like check the value if it is null,set the invisible bit
	# pop 0x0~0x3 into those registers will casue no exception
change_ds:
	enter $0,$0
	#suffix sometimes are not needed
	mov 16(%rbp),%ax
	mov %ax,%ds
	leave
	ret
