
#include "protected_mode.h"
/**
 * To enter protected mode,the address line A20 must be set 
 * Well,it is initially enabled.But to ensure it is enabled,better to set it active.
 * The port 0x92(r/w)
 * 	bit	7~2		unused
 * 		1		enable A20
 *		0		restart computer
 */
#define PORT_92	0x92
void enable_A20()
{
	__asm__ __volatile__(
		"in %%bx, %%al \n\t"
		"or %%al, $0x02 \n\t"
		"out %%al, %%bx \n\t"
		:
		:"b"(PORT_92)
		:);
}


void reboot()
{
	__asm__ __volatile__(
		"movb	$0x01, %%al \n\t"
		"out %%al, %%bx \n\t"
		:
		:"b"(PORT_92)
		:);
}

