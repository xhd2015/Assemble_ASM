//=========FILE: start.h======
#ifndef __START_H__ /*START this file,define once*/
#define __START_H__

#include "asmstring.h"
#include "asmdef.h"
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
#define SET_GDT() \
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
#define SET_GDTM(len,addr) DEFW(,,len,_gdtm:); DEFL(,,addr)
#define SET_IDTM(len,addr) DEFW(,,len,_idtm:); DEFL(,,addr)
#define SET_STACK(offset) DEFLABLE(.org,offset,_stack:)
#define SET_BOOT(offset) DEFW(.org,offset,0xAA55)


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
#define CODE16GCC
__asm__(
".code16gcc\n\t");
#endif /*.codeXX ended */

/*This area of code is mode irrelative*/
/*But apparently,it is used to start the BIOS subroutine*/
/*Hence, it is always used to generate a BOOTLOADER.*/
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
#if defined CODE16GCC
"pushl $0\n\t"
"pushl $0\n\t"
#else 
"push $0\n\t"
"push $0\n\t"
#endif
"call main\n\t"
#if defined CODE16GCC
"addl $8,%esp\n\t"
#else
"addl $4,%esp\n\t"
#endif
"_die:\n\t"
"jmp _die\n\t"
);

#endif /* GENASM ended */

#endif /*END this file*/
