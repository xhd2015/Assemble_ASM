//=========FILE: libx2.c.h======
//=========ONLY 32-bit,both real & protected mode=======
#ifndef __LIBX2_C_H__ /*START this file,define once*/
#define __LIBX2_C_H__


//UNTESTED
#define FDEF_set_idt() \
void (short limit,int lineaddr) {\
        __asm__ __volatile__(\
        "movw (4+4*1)(%%ebp),%%ax \n\t"\
        "movw %%ax,(4+4*1+2)(%%ebp) \n\t"\
        "lidt %%ss:(4+4*1+2)(%%ebp) \n\t"\
        :::);}
                    
//UNTESTED
#define FDEF_set_gdt() \
void set_gdt(short limit,int lineaddr) {\
        __asm__ __volatile__(\
        "movw (4+4*1)(%%ebp),%%ax \n\t"\
        "movw %%ax,(4+4*1+2)(%%ebp) \n\t"\
        "lgdt %%ss:(4+4*1+2)(%%ebp) \n\t"\
        :::);}
            
//TESTED
//regs:es
#define FDEF_memcopy() \
int memcopy(int segfrom,int offsetfrom,int segto,int offsetto,int len) {\
        int moved;\
        __asm__ __volatile__(\
                "cld \n\t"\
                "push %%ds \n\t"\
                "mov %%ax, %%ds \n\t"\
                "mov %%bx, %%ax \n\t"\
                "mov %%ax, %%es \n\t"\
                "rep movsb \n\t"\
                "pop %%ds \n\t"\
                :"=c"(moved)\
                :"a"(segfrom),"b"(segto),"c"(len),"S"(offsetfrom),"D"(offsetto)\
                :   \
        );  \
        return moved;\
}



#endif /*END this file*/
