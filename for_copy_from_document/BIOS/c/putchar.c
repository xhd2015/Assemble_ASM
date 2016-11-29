
#include "putchar.h"
#include "asmdef.h"

int putchar(char ch,char bg,int pos) /*return next pos,if meet with '\r' or '\n'*/
{
	__asm__ __volatile__(
		"mov 8(%%ebp),%%cl \n\t"
		"mov 12(%%ebp),%%ch \n\t"
		"mov 16(%%ebp),%%ebx \n\t"
		"mov $" STRING(VIDEOBASE) ", %%ax \n\t"
		"mov %%ax, %%es \n\t"
		"movw %%cx, %%es:(%%ebx) \n\t"
		"mov %%ebx,%%eax \n\t"
		"inc %%eax \n\t"
		"inc %%eax \n\t"
		:	
		:
		:"ecx","ebx");		
}

int putstr(char *str,char bg,int pos)
{
	int uppos=pos;
	while(*str)
	{
		uppos=putchar(*str,bg,uppos);
		str++;
	}
	return uppos;
}


void clear_screen(int count)
{
	for(int i=0;i<count;i++)
		putchar(0,0,i);
}

