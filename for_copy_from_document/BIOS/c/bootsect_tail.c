
#include "start.h"
#include "asmdef.h"

DEFGLOBAL(_stack);
DEFGLOBAL(_idtm);
DEFGLOBAL(_gdtm);
DEFGLOBAL(_gdt);

DEFLABLE(,,_logical_zero_pos:);
//================Set the Image Content=========
//These SET_XXX are macros counld be found in "start.h"

SET_GDT() ;/*_gdt used*/
SET_GDTM(0x07FF,_gdt+0x7c00) ;
SET_IDTM(0,0) ;
DEFL(,,_logical_zero_pos);
DEFSYM(last_len,350);
/*The effective address rely on the last segment ending address*/

/*stack from 505*/
SET_STACK(505-last_len) ;
SET_BOOT(510-last_len) ;


