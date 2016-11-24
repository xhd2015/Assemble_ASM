#include "int16.h"

short peekchar() /*L:ascii H:scan code. if 0, there is not key*/
{
	__asm__ __volatile__(
		"mov $0x11, %%ah \n\t"
		"int $0x16	\n\t"
		"jz 1f		\n\t"
		"1: \n\t"
		"xor %%ax,%%ax\n\t"
		:
		:
		:"cc");
}

short getchar()
{
	__asm__ __volatile__(
		"mov $0x10, %%ah \n\t"
		"int $0x16	\n\t"
		:
		:
		:);
}
