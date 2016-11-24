
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
