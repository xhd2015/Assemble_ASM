#hello.s
	.code32 #under 32 , to make pushl,popl work normally
	.data
msg:	.string "Hello World !\n"
	len =	. -msg
arr:	.byte 45,56
	.text
	.global _start  #entry

_start:
	movl $_start,%edx
#	movb _start,%dl
#	movb %cs:_start,%dl
#	movb %ds:_start,%dl
mydefined:	
	movl $0,%ebx
	movl %cs:(mydefined+5)(%ebx),%edx
	#this style finally works,we have explored its mechanism
	#some keywords:
	#	defualt: ds , eip
	#	meet only at the really request moment
	#At runtime,the initial value of _start,which is not zero,indicating that there is some header between the base and the start point
	
	
	# if no ebx speciefied,eip is used.
	# if no :prefix speciefied,ds is used
	# can you tell me what had they actually generated?


	movl %edx,msg(%ebx)
	#	read from ebx to the "Hello world"
	mov msg(%ebx),%edx
	#	these two instructions had shown that the data section is writeable
	#	the only unresolved question is , how can the data be acessed with a null segment selector?It cannot be start from the real address
	#=======Save gdt : get 0x2ee09000007f = 32-bit base + 16-bit limit. Here,base=0x2ee09000  limit=0x007f
	#with more info , we know ds,es,fs,gs=0,cs=0x33,ss=0x2b
	#cs=gdt[6]   cs:-->gdt[6].base<<4
	#ss=gdt[5]
	#every item of gdt has 8 bytes
	#	base_high(1)+attributes(2)+seg_base_middle_low(3)+seg_limit(2)
	sgdt msg(%ebx)
	sgdt (msg+6)(%ebx)
	
	#=======If consider that ds is the virtual address base,it should be set to 0,to allow us to fetch any content from the system,though we cannot modify those data at our own.
	#but was later proved wrong or at least not completely right.
	#under the protected mode , we're limited to reference to the memory that is a segment.Since GDT is not in a segment,it is not possible for us to get known of it.
	#It's because any address we give , will be constraints to a specific prefix,that prefix is just a limited space of the memory.We have at most 6 segments in one program.The .bss is finally merged into the .data segment
	movl $0,%ebx
	GDT_BASE = 0x2ee09000
	#	movl GDT_BASE(%ebx),%eax
	#		get SIGSEGV
	
	movl $len,%edx
	movb $79,%al
#	movb %al,%ds:msg #generate movabs %al,0x600127b9:0x00600127
	#the unshadowed part of ds is 0,but the shadowed part remains the valid address.
	#	movb %al,msg
	#		this generates exactly the same thing as the above one.One thing to pay attention to,the segment address is not immediately combined with the offset that make a complete one at the compile time.The segment informatoin combining with an offset is kept until there is a chance to use them,that's the only time they can meet with each other.
	#	so the segment .text is not accessiable under the condition ds=0.But why it can be visited?
	#	and note that with memory access , msg will be extended
	#	movb msg,%cl
	#		got SIGSEGV
	#automatically generated as movb 0x600128(%eip),%cl, means %cs:msg(%eip)
	#	movb msg(%ip),%cl
	#		but never should ip directly used
	#	movb %cs:msg,%cl
	#		gen: %cs:msg(%eip),%cl , also got SIGSEGV
	movb msg,%cl
	movl $msg,%ecx
	movl $1,%ebx
	movl $4,%eax
	int $0x80

	movl $len,%edx
	leal msg,%ecx  #if no prefix given,ds assumed
	#the default is that , is an instruction is
	#related to data operation, ds: used ; related to code, cs: used , esp related , ss is used
	movl $1,%ebx
	movl $4,%eax
	int $0x80
	movl $len,%edx
#	pushb $0x44  #unsupported
	pushw $0x3333
	#for push , once you can push 1 byte or 4 bytes.2 is considered to be 1.
	movzwl (%esp),%eax
	pushl $0x11112222
	movl (%esp),%eax  # ss is assumed. esp+4  esp+3  esp+2 esp+1 esp
		#after pushx any thing,you don't need to calculate these offset by yourself,instead you'll always use movx %(esp),...
	#which segment is used?
	popl %eax
	popw %ax

	#use test to clearify that

	#=========Test START : segment descriptor.(ds=es=fs=gs)=========
	# IP,CS can't be used in dst
#	movl %cs:0,%eax
	#tested , cs can't be used here
	#	leal %cs:0,%ebx
#	movl %ds:msg,%eax
	movl $msg,%eax
	movl $10,%es:(%eax)
	
	#========Test END=========
	#=========Test START=========
	
	#========Test END=========
	#=========Test START:JMP & RET=========
	call _dump_ds_to_ax_as_call
	#========Test END=========
	#=========Test START  :  Call=========
#	jmp _dump_cs_to_ax
	#========Test END=========

	#=========Test START  : LIDT , SIDT -- CPL , IDTR =========
	movl $msg,%ebx
	#	SIDT %ebx
	#error : unsupported instruction
	#========Test END=========
	#=========Test START  :  iret int  -- IDT=========
	#when the computer starts,the operation system as a software and a provider should firstly set the IDT.IDT is pointed by a register , which will have different values in different modes,like real mode and protection mode.
	#========Test END=========

	#=========Test START  :  Call=========
	jmp _dump_cs_to_ax
	#========Test END=========


	
	movl $0,%ebx
	movl $1,%eax
	int $0x80
	#some information about using gdb
	#format  x/nfu	addr
	#	n--->how many trunck to show
	#	f--->format , x:hex
	#	u---->length of trunck, b:Byte, h:Halfword,w:Word
	# x/10xb	0x7fffffff2430
	
_dump_cs_to_ax:
	movw %cs,%ax
_dump_ds_to_ax_as_call:
	movw %ds,%ax
	ret
