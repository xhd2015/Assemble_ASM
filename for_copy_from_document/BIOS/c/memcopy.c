#include "memcopy.h"

/**
 * ds:si --> es:di
 * a word each time.
 */
int memcopy(int segfrom,int offsetfrom,int segto,int offsetto,int len)
{
	int moved;
	__asm__ __volatile__(
		"cld \n\t"
		"push %%ds \n\t"
		"mov %%ax, %%ds \n\t"
		"mov %%bx, %%ax \n\t"
		"mov %%ax, %%es \n\t"
		"rep movsb \n\t"
		"pop %%ds \n\t"
		:"=c"(moved)
		:"a"(segfrom),"b"(segto),"c"(len),"S"(offsetfrom),"D"(offsetto)
		:
	);
	return moved;
}

