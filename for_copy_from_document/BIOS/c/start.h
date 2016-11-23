//=========FILE: start.h======
#ifndef __START_H__ /*START this file,define once*/
#define __START_H__

#include "asmstring.h"
#include "asmdef.h"
/**
 *Include this file to a c source file
 *
 *See the macros defined below.
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
//======Macro SET_GDT=====
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


//=========Macro GODIE========
#define GODIE()	\
	DEFOP0(_die:);\
	DEFOP1(jmp,_die)

//=========Macro GENLOADER========
#define GENLOADER(seg,stackoff,entry) \
__asm__ ( \
".global _start\n\t" \
".text\n\t" \
"_start:\n\t" \
"ljmp $" STRING(seg)", $_here\n\t" \
"_here:\n\t" \
"mov %cs,%ax\n\t" \
"mov %ax,%ds\n\t" \
"mov %ax,%es\n\t" \
"mov $" STRING(stackoff) ", %eax\n\t" \
"mov %eax,%esp\n\t" \
"pushl $0\n\t" \
"pushl $0\n\t" \
"call " STRING(entry) " \n\t" \
"addl $8,%esp\n\t" );\
GODIE()



#endif /*END this file*/
