#define GENASM
#define CODE16GCC
#include "start.h"

#define SYSSEG 0x1000
#define SYSLEN 17

int copy_seg(int segfrom,int offsetfrom,int segto,int offsetto,int len);
void LBA_read(int offset,int start,int num);

int main(int argc,char* argv[])
{

	
	/*Load System Kernel Image*/
	LBA_read(SYSSEG,0,SYSLEN);

	/*Copy the Head Image from 0x1000 to 0x0*/
	/*8 KB*/
	copy_seg(SYSSEG,0,0,0,0x1000);
	
	/*Set the IDT & GDT Registers*/
		

	/*Enter Protected Mode*/
	/*Load IDTR & GDTR from _idtm and _gdtm,Then Set the CR0(PE)=1,Jump.*/
	START_PROTECTED_MODE(_idtm,_gdtm,0x8,0x0);
	
	/*If the kernel ended like a normal program,back here,it will go die*/
	/*But actually,I think no such kernel will return back here*/
	return 0;
}
/**
 * ds:si --> es:di
 * a word each time.
 */
int copy_seg(int segfrom,int offsetfrom,int segto,int offsetto,int len)
{
	int moved;
	__asm__ __volatile__(
		"cli \n\t"
		"push %%ds \n\t"
		"mov %%ax, %%ds \n\t"
		"mov %%bx, %%ax \n\t"
		"mov %%ax, %%es \n\t"
		"rep movsw \n\t"
		"pop %%ds \n\t"
		"sti \n\t"
		:"=c"(moved)
		:"a"(segfrom),"b"(segto),"c"(len),"S"(offsetfrom),"D"(offsetto)
		:
	);
	return moved;

}
/**
 * Use LBA28 to read hard disk.SEE the book ISBN 9787121187995,page 125
 * This is an alternative of using BIOS int 0x13 to read logical sectors
 */
#define PORT_SECNUM	0x1f2
 /*0 to read 256 sectors */

#define PORT_SECSTART	0x1f3
#define PORT_MODE	0x1f6
/*
 *bit 	7	1 reserved
 *	6	0:CHS 1:LBA
 *	5	1 reserved
 *	4	0:Master 1:Slave
 *	3~0	corresponding to the 27~24 bits of Logical Number
 *
 */

#define PORT_READY	0x1f7
/*
 *bit	7	1:Busy 0:Ready
 *	6~4	Unknown
 *	3	1:Ready
 *	2~1	Unknown
 *	0	1:Error Happened 0:Successful
 */

#define PORT_ERROR	0x1f1
#define PORT16_DATA	0x1f0
/*
 *cx	double-bytes count (e.g. word count)
 */

//===============LBA Programs============
#define LBA_SET_COUNT(num) \
	OUT_PORT(PORT_SECNUM,num)

/*An LBA28 sector number is 28-bit long*/
#define LBA_SET_START(start) ({ \
	OUT_PORT(PORT_SECSTART,(char)start);\
	start=start>>8;\
	OUT_PORT(PORT_SECSTART+1,(char)start);\
	start=start>>8;\
	OUT_PORT(PORT_SECSTART+2,(char)start);\
	start=(start>>8) & 0xef;\
	OUT_PORT(PORT_SECSTART+3,(char)start);})


/*After sending the read request, it needs some time to let it be ready.*/
#define LBA_WAITFOR ({ \
	char status; \
	while(1) \
	{	\
		READ_PORT(PORT_READY);\
		ASSIGN_VALUE(status);\
		status = status & 0x88;/*Test bit 7 and 3*/\
		if(status == 0x08)/* Not Busy and Ready */\
		{ \
			break;\
		}\
	} })

#define LBA_RETRIVEDATA(offset,count) \
	__asm__ __volatile__(\
		"1: \n\t" \
		"in %%dx, %%ax \n\t" \
		"movw (%%bx), %%ax \n\t" \
		"inc %%bx \n\t" \
		"inc %%bx \n\t" \
		"loop 1b \n\t" \
		: \
		:"d"(PORT16_DATA),"b"(offset),"c"(count) \
		:"eax")

/**
 *Read the sectors from 'start',upto start+num.
 *Load the data to ds:offset
 */
void LBA_read(int offset,int start,int num)
{
	LBA_SET_START(start);

	LBA_SET_COUNT(num);
	OUT_PORT(PORT_READY,0x20);
	LBA_WAITFOR ;
	LBA_RETRIVEDATA(offset,num*512/2); /*read a word each time*/
}

//================Set the Image Content=========
//These SET_XXX are macros counld be found in "start.h"

SET_GDT ;/*_gdt used*/
SET_GDTM ;
SET_IDTM ;

/*stack from 505*/
SET_STACK ;
SET_BOOT ;


