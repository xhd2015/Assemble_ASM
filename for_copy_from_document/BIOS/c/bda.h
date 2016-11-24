//=========FILE: bda.h======
//=========BIOS Data Area Utils=====
#ifndef __BDA_H__ /*START this file,define once*/
#define __BDA_H__

#define BDASEG		0x40
#define BDACOL		0x4A	/*0x4A,0x4B*/
#define BDAMEMSIZE	0x13 	/*0x13,0x14   unit:KB*/

int get_screen_column();



#endif /*END this file*/

