
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
	setint(0x8,BOOTSEG,putter);			/*set int 0x8*/
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
