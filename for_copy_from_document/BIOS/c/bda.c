
#include "bda.h"
#include "asmdef.h"

int get_screen_column()
{
	int col;
	MGETL(col,BDASEG,BDACOL);
	return (col & 0x0000ffff)*2;
}
