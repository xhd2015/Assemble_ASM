
#include "start.h"
#include "asmdef.h"

DEFGLOBAL(_idtm);
DEFGLOBAL(_gdtm);
DEFGLOBAL(_gdt);
DEFGLOBAL(_stack);

DEFSYM(_stack,512*2);      /* set _stack to the third sector*/
