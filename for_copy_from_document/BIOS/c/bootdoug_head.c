
#define CODE16GCC
#include "start.h"
#include "int13.h"
#include "memcopy.h"
#include "putchar.h"

#define SYSSEG 0x1000
#define SYSLEN 1
#define SECSIZE 512
#define BOOTSEG 0x7c0

GENLOADER(BOOTSEG,_stack,enter_main);

int enter_main(int argc,char* argv[]) /*don't use main, gcc will change something*/
{
	int pos;
	read_sector(BOOTSEG,SECSIZE,0,0,0,2,1); /* read logical the 1 sector */
	pos=putstr("Loader by Douglas Fulton Shaw",MODE_WB,0);
	pos++;pos++;
	pos=putstr("Loading System Image.Verifying, Hold on.",MODE_WB,pos);
	memcopy(BOOTSEG,SECSIZE,0,0,SYSLEN*SECSIZE);

	return 0;
}

