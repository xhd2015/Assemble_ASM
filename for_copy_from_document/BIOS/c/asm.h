#ifndef __ASM_H__
#define __ASM_H__
#include "asmstring.h"
/**
 *These codes are mode independent,can be compiled using
 *16-bit or 32-bit options.
 *The only thing to *remember* is that,it is portable to
 *different modes.
 */

#define _STRING(x) #x
#define STRING(x) _STRING(x)

/*An optional lable*/
#define _DEF(loc,off,type,data,lable) \
__asm__(STRING(loc) " " STRING(off) "\n\t" \
	STRING(lable) "\n\t"\
        STRING(type) " " STRING(data) "\n\t")

#define DEFB(loc,off,data,lable...) _DEF(loc,off,.byte,data,lable)
#define DEFW(loc,off,data,lable...) _DEF(loc,off,.word,data,lable)
#define DEFL(loc,off,data,lable...) _DEF(loc,off,.long,data,lable)
#define DEFLABLE(loc,off,lable)		_DEF(loc,off,,,lable)
/*maybe useful: def in current position*/
/**
 *usage:
 * DEFW(.org,510,0x55AA,_boot_flag:)
 * DEFL(,,0x78)
 * DEFLABLE(.org,505,_stack:)
 * DEF
 *
 */



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


#endif /*this file end*/
