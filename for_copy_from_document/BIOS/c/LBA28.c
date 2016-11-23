#include "LBA28.h"
#include "asmport.h"


/**
 *Read the sectors from 'start',upto start+num.
 *Load the data to ds:offset
 * use num to determine the sector count.
 */
void LBA_read(int dst_offset,int sec_start,int num)
{
	LBA_SET_START(sec_start);
	LBA_SET_COUNT(num);
	OUT_PORT(LBAPORT_READY,0x20);
	LBA_WAITFOR() ;
	LBA_RETRIVEDATA(dst_offset,num*512); /*read a word each time*/
}


