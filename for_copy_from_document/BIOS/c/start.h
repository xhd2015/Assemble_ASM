
/**
 *Include this file to a c source file
 *
 * define GENASM to enable the _start inserted.
 * define CODE16 for .code16
 * define CODE16GCC for .code16gcc
 * define CODE32 for .code32
 * define CODE64 for .code64 
 * 
 * if none of them is defined,then choose .code16gcc as default.
 * 
 * Currently, the combination of GENASM with CODE16GCC(default one) works fine.
 *
 * The defined MACROs are
 * STACK
 * BOOT
 */

#define _STRING(x) #x
#define STRING(x) _STRING(x)


#define OUT_PORT(port,data) \
__asm__ __volatile__(\
	"out %%al, %%dx \n\t"\
	:\
	:"d"((port)),"a"((data)) \
	:)
#define READ_PORT(port) \
__asm__ __volatile__(\
	"in %%dx, %%al \n\t"\
	:\
	:"d"((port)) \
	:)
#define READ_PORTW(port) \
__asm__ __volatile__(\
	"in %%dx, %%ax \n\t"\
	:\
	:"d"((port))\
	:)

#define ASSIGN_VALUE(var) \
__asm__ __volatile__(\
	""\
	:"=a"(var)\
	:\
	:)

#define START_PROTECTED_MODE(idt,gdt,new_seg,new_off) \
__asm__ __volatile__(\
	"lidt	" STRING(idt) " \n\t" \
	"lgdt	" STRING(gdt) " \n\t"  \
        "lmsw   %%ax \n\t"\
        "ljmp   $" STRING(new_seg) ", $" STRING(new_off) " \n\t"\
        :\
        :"a"(0x0001)\
        :)

/**
 *define gdt
 */
#define SET_GDT \
__asm__("_gdt:\n\t"\
	".word 0,0,0,0 \n\t" \
	".word 0x07FF \n\t" \
	".word 0x0000 \n\t" \
	".word 0x9A00 \n\t" \
	".word 0x00C0 \n\t" \
	\
	".word 0x07FF \n\t" \
	".word 0x0000 \n\t" \
	".word 0x9200 \n\t" \
	".word 0x00C0 \n\t" )
/**
 *set gdt descriptor,which will be later loaded to GDTR
 *GDTM , corresponding to GDTR,M denotes the memory
 */
#define SET_GDTM \
__asm__("_gdtm: .word 0x07FF \n\t" \
	"	.word 0x7C00+_gdt , 0 \n\t" )

/**
 *Simply set it unused
 */
#define SET_IDTM \
__asm__("_idtm: .word 0 \n\t" \
	"	.word 0, 0 \n\t" )
#define SET_STACK \
__asm__(".org 505\n\t"\
	"_stack:\n\t")


#define SET_BOOT \
__asm__(".org 510\n\t"\
	".word 0xAA55\n\t")

//=========Macro GENASM========

#if defined GENASM


#if defined CODE16
__asm__(
".code16\n\t");
#elif defined CODE32
__asm__(
".code32\n\t");
#elif defined CODE64
__asm__(
".code64\n\t");
#else
__asm__(
".code16gcc\n\t");
#endif /*.codeXX ended */



__asm__ (
".global _start\n\t"
".text\n\t"
"_start:\n\t"
"ljmp $0x7c0,$_here\n\t"
"_here:\n\t"
"mov %cs,%ax\n\t"
"mov %ax,%ds\n\t"
"mov %ax,%es\n\t"
"mov $_stack,%eax\n\t"
"mov %eax,%esp\n\t"
"pushl $0\n\t"
"pushl $0\n\t"
"call main\n\t"
"addl $8,%esp\n\t"
"_die:\n\t"
"jmp _die\n\t"
);

#endif /* GENASM ended */

