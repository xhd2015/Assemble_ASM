//=========FILE: libx2.h======
//=========ONLY 32-bit, consistence prefect========
#ifndef __LIBX2_H__ /*START this file,define once*/
#define __LIBX2_H__


#define FDEC_atos() \
	int atos(int x,char *p)
#define FDEC_reverse() \
	void reverse(char* start,char* end)
#define FDEC_setint() \
	void setint(char intn,short seg,short off)
#define FDEC_settimeval() \
	void settimeval(int timeval) 


#define FDEFATOS()\
int atos(int x,char *p) {\
	int sign=0; \
	char* previous=p; \
	char temp; \
	if(x<0){sign=-1;x=-x;} \
	while(x>0) \
	{ \
		*p++ = x%10+'0'; \
		x /=10;\
	} \
	if(sign==-1) \
	{ \
		*p++='-'; \
	} \
	*p--=0;\
	reverse(previous,p); \
	\
	return(p - previous);}
/*Very huge depression.Compare in AT&T,reversed order.*/
#define FDEFREVERSE()\
void reverse(char* start,char* end) \
{\
	__asm__ __volatile__(\
		"push %%edx \n\t"\
		"push %%ebx \n\t"\
		"movl (4+4*1)(%%ebp), %%ebx \n\t"\
		"movl (4+4*2)(%%ebp), %%edx \n\t"\
		"cmp %%edx,%%ebx \n\t" \
		"jae	2f \n\t" \
		"1: \n\t" \
		"mov (%%ebx),%%al \n\t" \
		"xchgb %%al, (%%edx) \n\t" \
		"movb %%al, (%%ebx) \n\t" \
		"inc %%ebx \n\t" \
		"dec %%edx \n\t" \
		"cmp %%edx, %%ebx \n\t"\
		"jb 1b \n\t"\
		"2: \n\t" \
		"pop %%ebx \n\t"\
		"pop %%edx \n\t"\
		: \
		: \
		:);}

#define FDEFSETINT() \
void setint(char intn,short seg,short off) {\
        __asm__ __volatile__(    \
		"pushf \n\t" \
		"cli \n\t"                 \
		"push %%ebx \n\t" \
                "push %%es \n\t" \
                "xor %%ax,%%ax \n\t" \
                "mov %%ax,%%es \n\t"  \
		"mov (4+4*1)(%%ebp),%%ebx \n\t" \
		"shl $0x2,%%ebx \n\t" \
                "movw (4+4*2)(%%ebp),%%ax \n\t" \
                "movw %%ax,%%es:2(%%ebx) \n\t" \
		"movw (4+4*3)(%%ebp),%%ax \n\t" \
                "movw %%ax,%%es:(%%ebx) \n\t" \
                "pop %%es \n\t" \
		"pop %%ebx \n\t" \
		"popf \n\t" \
                : \
                : \
                :);}

/*rhz = 11930180/gmv, rtm = gmv / 11930180, gtm = rtm * 1000 , gmv = 11930180 * gtm / 1000 */
/*unit : ms*/
/*example : 0.01ms , 1000 ms */
#define FDEFSETTIMEVAL() \
void settimeval(int timeval) \
{ \
	short freq= 1193 * timeval ;\
	__asm__ __volatile__( \
		"pushf \n\t"\
		"cli \n\t"\
		"push %%eax \n\t" \
		"push %%edx \n\t" \
		"movb $0x36, %%al \n\t" \
		"movw $0x43, %%dx \n\t" \
		"out %%al, %%dx \n\t" \
		"mov $0x40, %%dx \n\t" \
		"mov %%cl, %%al \n\t" \
		"out %%al, %%dx \n\t" \
		"mov %%ch, %%al \n\t" \
		"out %%al, %%dx \n\t" \
		"pop %%edx \n\t" \
		"pop %%eax \n\t" \
		"popf \n\t"\
		: \
		:"c"(freq) \
		:); \
}


#define FDEFREADTIMEVAL() \
short readtimeval() {\
	__asm__ __volatile__(\
		""\
		:::);}


#endif /*END this file*/
