//=========FILE: libx2.r.h======
//=========ONLY 32-bit, real mode===
#ifndef __LIBX2_R_H__ /*START this file,define once*/
#define __LIBX2_R_H__
#define FDEC_enter_protected_mode() \
void enter_protected_mode(short idtlimit,int idtbase,short gdtlimit,short gdtbase,short selector,int offset)

#define FDEF_enter_protected_mode() \
void enter_protected_mode(short idtlimit,int idtbase,short gdtlimit,int gdtbase,short selector,int offset){ \
	set_idt(idtlimit,idtbase);\
	set_gdt(gdtlimit,gdtbase);\
	__asm__ __volatile__(\
	"mov $0x1,%%cr0 \n\t"\
	"ljmp *%%bx,%%eax \n\t"\
	:\
	:"b"(selector),"a"(offset)\
	:);}
		


#endif /*END this file*/
