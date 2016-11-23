//=========FILE: asmport.h======
#ifndef __ASMPORT_H__ /*START this file,define once*/
#define __ASMPORT_H__

#define OUT_PORT(port,data) \
__asm__ __volatile__(\
        "out %%al, %%dx \n\t"\
        :\
        :"d"((port)),"a"((data)) \
        :)
#define READ_PORT(port) \
__asm__ __volatile__(\
        "in %%dx, %%al \n\t"\
        :\
        :"d"((port)) \
        :)
#define READ_PORTW(port) \
__asm__ __volatile__(\
        "in %%dx, %%ax \n\t"\
        :\
        :"d"((port))\
        :)

#define ASSIGN_VALUE(var) \
__asm__ __volatile__(\
        ""\
        :"=a"(var)\
        :\
        :)

#endif /*END this file*/
