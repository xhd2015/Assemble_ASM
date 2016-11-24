#include "int13.h"
/*If hard drive wanted,the drive(7)=1*/
int read_sector(int seg,int off,char driver,char head,short cylinder,char sector,char count)
{
	int errn;
	__asm__ __volatile__(
		"push %%es \n\t"
		"push %%ebx \n\t"
		"push %%edx \n\t"
		"push %%ecx \n\t"
		"mov (4+4*1)(%%ebp), %%eax \n\t"
		"mov %%ax, %%es \n\t"
		"mov (4+4*2)(%%ebp), %%ebx \n\t"
		"mov (4+4*3)(%%ebp), %%dl \n\t"
		"mov (4+4*4)(%%ebp), %%dh \n\t"
		"mov (4+4*5)(%%ebp), %%ax \n\t"
		"mov %%al, %%ch \n\t"
		"mov (4+4*6)(%%ebp), %%cl \n\t"
		"and $0x03, %%ah \n\t"	/*keep 7~6*/
		"and $0xCF, %%cl \n\t" /*keep 5~0*/
		"or  %%ah, %%cl\n\t"
		"mov $0x02, %%ah \n\t"
		"mov (4+4*7)(%%ebp), %%al \n\t"
		"int $0x13 \n\t"
		"pop %%ecx \n\t"
		"pop %%edx \n\t"
		"pop %%ebx \n\t"
		"pop %%es \n\t"
		:"=a"(errn)
		:
		:);
	return errn>>8;/*ah is the error code*/
}



/**
 * ====BIOS: int 0x13====
 * ah=0x2		read to memory
 * al			sector count to read
 * ch			cylinder(7~0)
 * cl	BIT 	5~0	starting sector
 * 		7~6	cylinder(9~8)
 * dh			head
 * dl			driver number(if it is hard driver, then dl(7)=1)
 * es:bx		the target buffer
 * cf			if error cf=1,ah=error code
 */


