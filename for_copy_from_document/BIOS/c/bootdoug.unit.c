

#define CODE16GCC
#include "start.h"
#include "int13.h"

#define SYSSEG 0x1000
#define SYSLEN 1
#define SECSIZE 512
#define BOOTSEG 0x7c0
#define FILESIZE 8148

GENLOADER(BOOTSEG,_stack,enter_main);

void enter_mid();

int enter_main(int argc,char* argv[]) /*don't use main, gcc will change something*/
{
	read_sector(BOOTSEG,SECSIZE*2,0,0,0,3,(FILESIZE-SECSIZE)/SECSIZE); /* read logical the 3 sector,4 sectors */
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
#include "asmport.h"
#include "bda.h"
#include "putchar.h"
#include "memcopy.h"
#include "int13.h"
#include "int16.h"
#include "libx2.h"

#define NEWLINE(line,pos) \
	(line)++;\
	(pos)=0
DEFGLOBAL(_stack);			/*declare _stack for everything*/
DEFSYM(_stack,512*2);			/* set _stack to the third sector*/
DEFW(.org,510,0xAA55);			/* set boot flag */
DEFLABLE(.org,512*2,);			/*leave the second sector for stack*/

__asm__ (".string \"Now can you see me, Douglas Fulton Shaw?\" \n\t"); /*The verifying information for sector loading*/
DEFLABLE(.org,.+1,); /*a trailing 0 may cause unnecessary decoding issue,so add one*/


int atos(int x,char *p);
void reverse(char* start,char* end);
void putter();
void new_int13();
void new_int12();
void settimeval(int timeval);
void manager();
void taskA();
void taskB();

FDEFREVERSE();
FDEFATOS();
FDEFSETINT();
FDEFSETTIMEVAL();

#define MAXCOL 80
#define MAXROW 25
int curx,cury;
int col;

void enter_mid()
{
        col=get_screen_column();
	clear_screen(col*MAXROW); /*  80*25  text mode */
        cury=putstr("Loader by Douglas Fulton Shaw",MODE_WB,curx*col+cury);
        cury= (cury + 2) % col;
        curx++;
        cury=putstr("Loading System Image.Verifying, Hold on.",MODE_WB,curx*col+cury); 
	
	
	NEWLINE(curx,cury);
	putstr("Now hit a key...",MODE_WB,curx*col+cury);
        char ch=getchar();

	NEWLINE(curx,cury);
        cury=putstr("Input char is:",MODE_WB,curx*col+cury)%col;
        putchar(ch,MODE_WB,curx*col+cury)%col;

	NEWLINE(curx,cury);
	putstr("Welcome to X2 -- an OS designed by Douglas Fulton Shaw,2016",MODE_WB,curx*col+cury);
	
	NEWLINE(curx,cury);
	char container[4];
	int num=25;
	atos(num,container);
	putstr(container,MODE_WB,curx*col+cury);
	
	
	NEWLINE(curx,cury);
	putstr("Setting up interrupt...",MODE_WB,curx*col+cury);
	//short pnew_int;
	setint(13,BOOTSEG,new_int13);
	setint(12,BOOTSEG,new_int12);
	//ASSIGN_VALUE(pnew_int,new_int8);
	settimeval(100); /*100ms = 0.1s every once*/
	setint(0x8,BOOTSEG,manager);			/*set int 0x8*/
			/*see http://www.bioscentral.com/misc/interrupts.htm*/
			//The problem is that,it works fine initially,but as time increments,it will stop at some point.I don't know why
			//It is because the stack overflows its boundary.
			//Supcurye the ss:=0x7c0  esp:=1024  -- paddr 0x8000
			//It finally stops at ss=0x7c0 esp=0xffff  -- 0x17bff
			//when esp = 0x0000ffff , add 4, it causes the Bounds Exception int 0x5
			//when eax = 0x0000ffff, add 4 , it becomes 0x000010003 -- normally
			//This has showed the difference between add and pop.Generally, reference to 
			//Real Address Mode Exceptions -- http://www.fermimn.gov.it/linux/quarta/x86/pop.htm
			//Interrupt 13 if any part of the operand would lie outside of the effective address space from 0 to 0FFFFH
			//when esp = 0,it decrements 4, forming 0x0000fffc -- in 16-bit
			//however, t
			//When it decrements to 0
			//
			//
			//0xf000:e9e6:10 11 12 13  15 
			//
			//real mode
			//12 Stack Fault(#SS)
			//13 General Protection(#GP) (DS CS ES GS FS fault,not SS fault)
			//16 Floating-Point Error(#MF)
			//
			//Protected Mode
			// 11: segment-not-present fault
			// 12: stack fault
			// 13: GP
			// 14: Page-Fault Exception
			// 
			// firstly, int 12=int 13.However,when int 13 happened.
			// if improperly set the code,it will cause the system reboot.
			// if int 13 happens,if it is stack fault,then it will happens always.Every
			// time it wants to push something,but the stack is full,it cause another int 13
			// .This is endless

	NEWLINE(curx,cury);
	putstr("Running tasks...",MODE_WB,curx*col+cury);
	NEWLINE(curx,cury);
	cury=putstr(">>",MODE_WB,curx*col+cury)%col;
	
        //memcopy(BOOTSEG,SECSIZE,0,0,SYSLEN*SECSIZE);
}

int flag=0;

void putter()
{
	__asm__ __volatile__(
		"cli \n\t"
		"mov $0x20, %%al \n\t"
		"out %%al, $0x20 \n\t" /*send EOI to 0x20 PIC*/
		"#mov (2*2+4)(%%ebp),%%ax\n\t"
		"#or $0x0200, %%ax \n\t"
		"#mov %%ax,(2*2+4)(%%ebp) \n\t"
		:::);
	int linearpos=curx*col+cury;
	if(flag==0){flag=1;putchar('_',MODE_WB,linearpos);}
	else if(flag==1){flag=2;putchar('\\',MODE_WB,linearpos);}
	else if(flag==2){flag=3;putchar('|',MODE_WB,linearpos);}
	else if(flag==3){flag=0;putchar('/',MODE_WB,linearpos);}
	__asm__ __volatile__(
		"leave \n\t"
		"sti \n\t"
		"iretw \n\t"  /*int 13 happens here.Always.When modified pushed FLAGS*/
				/*Now I know a little thing.int 13 always happens whenever I call iret.*/
		/*Such a fuck thing!*/
		:::);
}

int running=0;
int executed=0;
int enter_esp,enter_ebp;

void taskA()
{
	putstr("A is running",MODE_WB,curx*col+cury);
	DEFOP0(cli);
	for(int i=0;i<col;i++)
		putchar('A',MODE_WB,(curx+1)*col+i);
	DEFOP0(sti);
	putstr("A is ended",MODE_WB,(curx+2)*col+cury);
}

void taskB()
{
	putstr("B is running",MODE_WB,curx*col+cury);
	DEFOP0(cli);
	for(int i=0;i<col;i++)
		putchar('B',MODE_WB,(curx+1)*col+i);
	DEFOP0(sti);
	putstr("B is ended",MODE_WB,(curx+2)*col+cury);
}
/*This process is very special, it should be the system kernel runtime
 * the truely one.
 *
 * We know that taskA and taskB have their own process IDs.A process may be interrupted any 
 * time.When an interrupt comes,a task may not complete its work,so to keep its information
 * is key to implement the process management  to X2.Hence some extra status flag should be added to identify how a process should be handled  when it is interrupted.
 * One simple implementation is that,a process is a struct,which has the following information: init -- when started,  run -- when running  ,pause -- when interrupted,  resume -- when resumed
 *
 * Now it is time to discuss the manager process.It executes the task switching.So to keep the system running,it is absolutely needed to keep this particular process running,in a unified status.What we are talking about is not other thing,it is actually the interrupt 8,timer.
 * Some characteristic features the int 8 handler.It is endless,even the handler has an formal iret,it will be reinvoked as long as the system still runs.
 * So we should consider the following issues:1.If the manager is running,another manager invokation happening  2.If a manager has resumed/started a task,it will wait to return.During the task,the manager is invoked 3.If the manager finished a task and on returning happened a manager invokation 4.The manager finished and successfully return the go-die loop  5.The manager started in the go-die loop. 
 *
 * The states transition:
 *
 * q0  -- no  q0
 * 	  yes  q1
 * q1  -- normal invoke ,invokeing process ,q2
 * 	  before invoking,happened , q1
 * 	  after invoking,happened,q1
 * 	  normal exit, q0
 *
 * q2  -- no, normally execute and exit,q1
 *	  yes , save information , q1
 *
 *
 *
 */

#define READY 0
#define RUNNING 1
#define FINISHED 2

int last_process_id=1;
typedef struct{ /*very similar to the protected mode*/
	int eflags;
	short cs;
	short ds;
	short ss;
	short es;
	int eip;
	int esp;
	int eax;
	int ecx;
	int ebx;
	int edx;
	int esi;
	int edi;
} process_resume_info;

typedef struct{
	int id;
	int status;/*ready  running finished*/
	int result;
	process_resume_info* pri;
	void (*run)();	
} process_control_block;


void resume(process_control_block* ppcb)
{
	DEFOP0(cli);
	process_resume_info *p=ppcb->pri;
	if(ppcb->status==READY)
	{
		ppcb->status=RUNNING;
		DEFOP0(sti);
		DEFOP0(iretw);
	}
	DEFOP0(sti);

}

void manager()
{
	__asm__ __volatile__(
		"cli \n\t" /*preparing clean stack*/
		:::);
	if(executed==0)
	{
		__asm__ __volatile__(
			"mov %%esp,enter_esp \n\t"
			"mov %%ebp,enter_ebp \n\t"
			:::);
		executed=1;
	}else{
		__asm__ __volatile__(
			"mov enter_esp,%%esp \n\t"
			"mov enter_ebp,%%ebp \n\t"
			:::);
	}
	__asm__ __volatile__(
		"sti \n\t"
		"mov $0x20,%%al \n\t"
		"out %%al,$0x20 \n\t"
		:::);
	if(running==0)
	{
		running=taskA;
		taskA();
	}else if(running==taskA){
		running=taskB;
		taskB();
	}else if(running==taskB){
		running=taskA;
		taskA();
	}
	executed=1;
	__asm__ __volatile__(
		"leave \n\t"
		"iretw \n\t"
		:::);
}

void new_int13()
{
	__asm__ __volatile__(
		"cli \n\t"
		:::);
	putstr("int 13",MODE_WB,2);
	__asm__ __volatile__(
		"leave \n\t"
		"iretw \n\t"
		:::);
}

void new_int12()
{
	__asm__ __volatile__(
		"cli \n\t"
		:::);
	putstr("int 12",MODE_WB,2);
	__asm__ __volatile__(
		"leave \n\t"
		"iretw \n\t"
		:::);
}


//The first interrupt(int go die loop) is 0xf000:e988 is int 9(key board)
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
	return (col & 0x0000ffff)*2;
}

#include "start.h"
#include "asmdef.h"

DEFGLOBAL(_idtm);
DEFGLOBAL(_gdtm);
DEFGLOBAL(_gdt);
