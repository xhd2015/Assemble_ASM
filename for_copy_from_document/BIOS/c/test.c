#include <stdio.h>
#include "asm.h"
#define _STRING(x) #x
#define STRING(x) _STRING(x)
#define START_PROTECTED_MODE(new_seg,new_off) \
__asm__ __volatile__(\
        "lmsw   %%ax \n\t"\
        "ljmp   $" STRING(new_seg) ", $" STRING(new_off) " \n\t"\
        :\
        :"a"(0x0001)\
        :)
#define FOO(a,b,c...) \
STRING(a) STRING(b) STRING(c)  STRING(\n)
int main()
{
	//START_PROTECTED_MODE(0x100,0x234);	
	printf(FOO(1,2));
	return 0;
}

DEFLABLE(.org,505,_stack:);
DEFW(.org,510,0x55AA);
DEFLABLE(,,asc:);
