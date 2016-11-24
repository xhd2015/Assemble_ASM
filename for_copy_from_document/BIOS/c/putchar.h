//=========FILE: putchar.h======
#ifndef __PUTCHAR_H__ /*START this file,define once*/
#define __PUTCHAR_H__

#define VIDEOBASE 0xb800
#define MODE_WB	0x07

int putchar(char ch,char bg,int pos);
int putstr(char *str,char bg,int pos);


#endif /*END this file*/
