

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

#include "int13.h"
/*If hard drive wanted,the drive(7)=1*/
int read_sector(int seg,int off,char driver,char head,short cylinder,char sector,char count)
{
	int errn;
	__asm__ __volatile__(
		"push %%es \n\t"
		"push %%ebx \n\t"
		"push %%edx \n\t"
		"push %%ecx \n\t"
		"mov (4+4*1)(%%ebp), %%eax \n\t"
		"mov %%ax, %%es \n\t"
		"mov (4+4*2)(%%ebp), %%ebx \n\t"
		"mov (4+4*3)(%%ebp), %%dl \n\t"
		"mov (4+4*4)(%%ebp), %%dh \n\t"
		"mov (4+4*5)(%%ebp), %%ax \n\t"
		"mov %%al, %%ch \n\t"
		"mov (4+4*6)(%%ebp), %%cl \n\t"
		"and $0x03, %%ah \n\t"	/*keep 7~6*/
		"and $0xCF, %%cl \n\t" /*keep 5~0*/
		"or  %%ah, %%cl\n\t"
		"mov $0x02, %%ah \n\t"
		"mov (4+4*7)(%%ebp), %%al \n\t"
		"int $0x13 \n\t"
		"pop %%ecx \n\t"
		"pop %%edx \n\t"
		"pop %%ebx \n\t"
		"pop %%es \n\t"
		:"=a"(errn)
		:
		:);
	return errn>>8;/*ah is the error code*/
}



/**
 * ====BIOS: int 0x13====
 * ah=0x2		read to memory
 * al			sector count to read
 * ch			cylinder(7~0)
 * cl	BIT 	5~0	starting sector
 * 		7~6	cylinder(9~8)
 * dh			head
 * dl			driver number(if it is hard driver, then dl(7)=1)
 * es:bx		the target buffer
 * cf			if error cf=1,ah=error code
 */



#include "start.h"
#include "asmdef.h"
#include "bda.h"
#include "putchar.h"
#include "memcopy.h"
#include "int13.h"
#include "int16.h"

#define NEWLINE(line,pos) \
	(line)++;\
	(pos)=0

DEFW(.org,510,0xAA55);			/* set boot flag */
DEFLABLE(.org,512*2,);			/*leave the second sector for stack*/

__asm__ (".string \"now can you see me, Douglas Fulton Shaw?\" \n\t"); /*a trailing 0 may cause unnecessary decoding issue,so add one*/
DEFLABLE(.org,.+1,);

void enter_mid()
{

        int pos;
        int col;
        int curline=0;
	pos = 0;
        col=get_screen_column()*2;
	clear_screen(col*25); /*  80*25  text mode */
        pos=putstr("Loader by Douglas Fulton Shaw",MODE_WB,curline*col+pos);
        pos = (pos + 2) % col;
        curline++;
        pos=putstr("Loading System Image.Verifying, Hold on.",MODE_WB,curline*col+pos); 
	
	
	NEWLINE(curline,pos);
	putstr("Now please hit a key...",MODE_WB,curline*col+pos);
        char ch=getchar();

	NEWLINE(curline,pos);
        pos=putstr("Input char is:",MODE_WB,curline*col+pos)%col;
        putchar(ch,MODE_WB,curline*col+pos)%col;

	NEWLINE(curline,pos);
	putstr("Welcome to X2 -- an OS designed by Douglas Fulton Shaw,2016",MODE_WB,curline*col+pos);
	
	NEWLINE(curline,pos);
	putstr(">>",MODE_WB,curline*col+pos);
	
        memcopy(BOOTSEG,SECSIZE,0,0,SYSLEN*SECSIZE);
}
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
#include "memcopy.h"

/**
 * ds:si --> es:di
 * a word each time.
 */
int memcopy(int segfrom,int offsetfrom,int segto,int offsetto,int len)
{
	int moved;
	__asm__ __volatile__(
		"cli \n\t"
		"push %%es \n\t"
		"push %%ds \n\t"
		"mov %%ax, %%ds \n\t"
		"mov %%bx, %%ax \n\t"
		"mov %%ax, %%es \n\t"
		"rep movsb \n\t"
		"pop %%ds \n\t"
		"pop %%es \n\t"
		"sti \n\t"
		:"=c"(moved)
		:"a"(segfrom),"b"(segto),"c"(len),"S"(offsetfrom),"D"(offsetto)
		:
	);
	return moved;

}


#include "putchar.h"
#include "asmdef.h"

int putchar(char ch,char bg,int pos) /*return next pos,if meet with '\r' or '\n'*/
{
	__asm__ __volatile__(
		"push %%es \n\t"
		"mov 8(%%ebp),%%cl \n\t"
		"mov 12(%%ebp),%%ch \n\t"
		"mov 16(%%ebp),%%ebx \n\t"
		"mov $" STRING(VIDEOBASE) ", %%ax \n\t"
		"mov %%ax, %%es \n\t"
		"movw %%cx, %%es:(%%ebx) \n\t"
		"mov %%ebx,%%eax \n\t"
		"inc %%eax \n\t"
		"inc %%eax \n\t"
		"pop %%es \n\t"
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

#include "bda.h"
#include "asmdef.h"

int get_screen_column()
{
	int col;
	MGETL(col,BDASEG,BDACOL);
	return col & 0x0000ffff;
}

#include "start.h"
#include "asmdef.h"

DEFGLOBAL(_idtm);
DEFGLOBAL(_gdtm);
DEFGLOBAL(_gdt);
DEFGLOBAL(_stack);

DEFSYM(_stack,512*2);      /* set _stack to the third sector*/
