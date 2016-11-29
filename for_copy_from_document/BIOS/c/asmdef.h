//=========FILE: asmdef.h======

#ifndef __ASMDEF_H__ /*START this file,define once*/
#define __ASMDEF_H__

#include "asmstring.h"



/*An optional lable*/
#define _DEF(loc,off,type,data,lable) \
__asm__(STRING(loc) " " STRING(off) "\n\t" \
        STRING(lable) "\n\t"\
        STRING(type) " " STRING(data) "\n\t")

#define DEFB(loc,off,data,lable...) _DEF(loc,off,.byte,data,lable)
#define DEFW(loc,off,data,lable...) _DEF(loc,off,.word,data,lable)
#define DEFL(loc,off,data,lable...) _DEF(loc,off,.long,data,lable)
#define DEFLABLE(loc,off,lable)         _DEF(loc,off,,,lable)
#define DEFGLOBAL(lable)	__asm__(".global " STRING(lable) " \n\t")
#define DEFSYM(sym,value)	__asm__(".set " STRING(sym) ", " STRING(value) " \n\t")
#define DEFCSYM(sym,value)	__asm__(STRING(sym) " = " STRING(value) " \n\t")
#define DEFOP(op,v1,v2)		__asm__(STRING(op) " " STRING(v1) ", "  STRING(v2) " \n\t")
#define DEFOP1(op,v1)		__asm__(STRING(op) " " STRING(v1) " \n\t")
#define DEFOP0(op)		DEFOP1(op,)

/*maybe useful: def in current position*/
/**
 *  *usage:
 *  * DEFW(.org,510,0x55AA,_boot_flag:)
 *  * DEFL(,,0x78)
 *  * DEFLABLE(.org,505,_stack:)
 *  * DEF
 *  *
 *  */

//#define DDEFOP(op,v1,v2) __asm__ __volatile__(\
		STRING(op) " %%eax, %%ebx \n\t" \
		: \
		:"a"(v1),"b"(v2)\
		:)


//===========Macro MGETL memory get long========
#define MGETL(var,seg,offset) ({\
__asm__ __volatile__(\
	"push %%edx \n\t" \
	"push %%ebx \n\t"\
	"push %%es \n\t"\
	"mov %%ax,%%es \n\t" \
	"movl %%es:(%%ebx),%%eax \n\t" \
	"pop %%es \n\t" \
	"pop %%ebx \n\t"\
	"pop %%edx \n\t"\
	:"=a"(var) \
	:"a"(seg),"b"(offset) \
	:);\
var;})
//MGETL(var,0,0x5*4);



//=====ebx ,eax,es are affected====
#define MGETLU(var,seg,offset) \
__asm__ __volatile__(\
	"mov %%ax,%%es \n\t"\
	"movl %%es:(%%ebx) %%eax \n\t" \
	:"=a"(var) \
	:"b"(offset),"a"(seg)\
	:)
//MGETLU(var,0,0x5*4);


#define MSETLU(var,seg,offset) \
__asm__ __volatile__(\
	"mov %%ax,%%es \n\t"\
	"movl %%edx, %%es:(%%ebx) \n\t" \
	: \
	:"b"(offset),"a"(seg),"d"(var)\
	:)
//MSETLU(var,0,0x5*4);

#endif /*END this file*/
