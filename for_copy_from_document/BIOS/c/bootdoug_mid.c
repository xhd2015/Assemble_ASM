
#include "start.h"
#include "asmdef.h"


//DEFSYM(logical_zero,0x1d5);	/*set offset of this file*/
DEFSYM(logical_zero,0);	/*set offset of this file*/

DEFW(.org,510 - logical_zero,0xAA55);	/* set boot flag */

__asm__ (".string \"now can you see me, Douglas Fulton Shaw?\" \n\t"); /*a trailing 0 may call unnecessary decoding issue,so add one*/
DEFLABLE(.org,.+1,);

