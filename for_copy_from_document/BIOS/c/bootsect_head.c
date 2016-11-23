/*start.h bootsect.c are independent to other files*/
/*They must be able to generate the 512-byte BIOS file*/
/*So to keep the target image file as small as possible,don't include any unnecessary files anymore*/
/*But it is possible to import the LBA28.h and memcopy.h,because they have been as smaller as they can be.*/


#define CODE16GCC
/*This area of code is mode irrelative*/
/*But apparently,it is used to start the BIOS subroutine*/
/*Hence, it is always used to generate a BOOTLOADER.*/



#include "start.h" /*some useful c implementations to asm*/
			/*include START_PROTECTED_MODE*/
#include "LBA28.h"
			/*include LBA_read*/
#include "memcopy.h"
			/*include memcopy*/


#define SYSSEG 0x1000
#define SYSLEN 17
#define SECSIZE 512
#define BOOTSEG	0x7c0

GENLOADER(BOOTSEG,_stack,main);

int main(int argc,char* argv[])
{
	/*Load System Kernel Image*/
	LBA_read(SYSSEG,0,SYSLEN);

	/*Copy the Head Image from 0x1000 to 0x0*/
	/*8 KB*/
	/*16*512 = 0x2000 Byte*/
	memcopy(SYSSEG,0,0,0,(SYSLEN-1)*SECSIZE);

	/*Enter Protected Mode*/
	/*Load IDTR & GDTR from _idtm and _gdtm,Then Set the CR0(PE)=1,Jump.*/
	START_PROTECTED_MODE(_idtm,_gdtm,0x8,0x0);
	
	/*If the kernel ended like a normal program,back here,it will go die*/
	/*But actually,I think no such kernel will return back here*/
	return 0;
}



