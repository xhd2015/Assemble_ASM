
#include "start.h"
#include "asmdef.h"

//DEFSYM(logical_zero,0x2d8+0x48);
DEFSYM(logical_zero,0);
DEFGLOBAL(_idtm);
DEFGLOBAL(_gdtm);
DEFGLOBAL(_gdt);
DEFGLOBAL(_stack);

DEFW(.org,512*2-100-logical_zero,0xAA55);	/*2 sectors */
DEFSYM(_stack,512*3);      /* set _stack to the third sector*/
