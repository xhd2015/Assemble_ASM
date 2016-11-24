//=========FILE: LBA28.h======
#ifndef __LBA28_H__ /*START this file,define once*/
#define __LBA28_H__

/**
 * Use LBA28 to read hard disk.SEE the book ISBN 9787121187995,page 125
 * This is an alternative of using BIOS int 0x13 to read logical sectors
 */
#define LBAPORT_SECNUM	0x1f2
 /*0 to read 256 sectors */

#define LBAPORT_SECSTART	0x1f3
#define LBAPORT_MODE	0x1f6
/*
 *bit 	7	1 reserved
 *	6	0:CHS 1:LBA
 *	5	1 reserved
 *	4	0:Master 1:Slave
 *	3~0	corresponding to the 27~24 bits of Logical Number
 *
 */

#define LBAPORT_READY	0x1f7
/*
 *bit	7	1:Busy 0:Ready
 *	6~4	Unknown
 *	3	1:Ready
 *	2~1	Unknown
 *	0	1:Error Happened 0:Successful
 */

#define LBAPORT_ERROR	0x1f1
#define LBAPORT16_DATA	0x1f0
/*
 *cx	double-bytes count (e.g. word count)
 */

//===============LBA Programs============

#define LBA_SET_COUNT(num) \
	OUT_PORT(LBAPORT_SECNUM,num)

/*An LBA28 sector number is 28-bit long*/
#define LBA_SET_START(start) ({ \
	OUT_PORT(LBAPORT_SECSTART,(char)start);\
	start=start>>8;\
	OUT_PORT(LBAPORT_SECSTART+1,(char)start);\
	start=start>>8;\
	OUT_PORT(LBAPORT_SECSTART+2,(char)start);\
	start=((start>>8) & 0x0f ) | 0xe0;\
	OUT_PORT(LBAPORT_SECSTART+3,(char)start);})


/*After sending the read request, it needs some time to let it be ready.*/
#define LBA_WAITFOR() ({ \
	char status; \
	while(1) \
	{	\
		READ_PORT(LBAPORT_READY);\
		ASSIGN_VALUE(status);\
		status = status & 0x88;/*Test bit 7 and 3*/\
		if(status == 0x08)/* Not Busy and Ready */\
		{ \
			break;\
		}\
	} })
/*offset: memory address to save data*/
/*count : byte count to be read*/
#define LBA_RETRIVEDATA(offset,count) \
	__asm__ __volatile__(\
		"1: \n\t" \
		"in %%dx, %%ax \n\t" \
		"movw %%ax, (%%bx) \n\t" \
		"inc %%bx \n\t" \
		"inc %%bx \n\t" \
		"loop 1b \n\t" \
		: \
		:"d"(LBAPORT16_DATA),"b"(offset),"c"(count/2) \
		:"eax")


/**
 *Read the sectors from 'start',upto start+num.
 *Load the data to ds:offset
 */
void LBA_read(int offset,int start,int num);

#endif
