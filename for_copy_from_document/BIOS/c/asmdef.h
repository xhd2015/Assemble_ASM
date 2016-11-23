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
#define DEFSYM(sym,value)	__asm__(STRING(sym) " = " STRING(value) " \n\t")
/*maybe useful: def in current position*/
/**
 *  *usage:
 *  * DEFW(.org,510,0x55AA,_boot_flag:)
 *  * DEFL(,,0x78)
 *  * DEFLABLE(.org,505,_stack:)
 *  * DEF
 *  *
 *  */

#endif /*END this file*/
