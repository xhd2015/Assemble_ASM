//=========FILE: int13.h======
#ifndef __INT13_H__ /*START this file,define once*/
#define __INT13_H__

int read_sector(int seg,int off,char driver,char head,short cylinder,char sector,char count);

#endif /*END this file*/

