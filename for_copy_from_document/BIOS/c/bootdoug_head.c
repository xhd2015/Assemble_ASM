
#define CODE16GCC
#include "start.h"
#include "int13.h"

#define SYSSEG 0x1000
#define SYSLEN 1
#define SECSIZE 512
#define BOOTSEG 0x7c0

GENLOADER(BOOTSEG,_stack,enter_main);

void enter_mid();

int enter_main(int argc,char* argv[]) /*don't use main, gcc will change something*/
{
	read_sector(BOOTSEG,SECSIZE*2,0,0,0,3,3); /* read logical the 1 sector */
	enter_mid();
	return 0;
}

