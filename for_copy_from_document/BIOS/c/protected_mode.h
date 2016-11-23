//=========FILE: protected_mode.h======
#ifndef __PROTECTED_MODE_H__ /*START this file,define once*/
#define __PROTECTED_MODE_H__

#define PROTECTED_MODE
/**
 *calling the routines here will assume that you have entered
 *protected mode.
 *
 *
 *
 *
 *
 *
 *
 */

/*constructure of GDTR*/
/**
 * define the needed type for protected mode
 * 
 *	gdtr,idtr,ldtr
 *	segment_descriptor (64-bit)
 *
 *
 */

typedef struct{
	short	limit;	/*16 bit limit*/
	int	base;/*32 bit linear address*/
}gdtr;

#define idtr gdtr
#define ldtr gdtr

typedef struct{
	short	limit_low;
	short	base_low;
	char	base_mid;
	char	privilage;/*P DPL(3) S TYPE(4)*/
				/*P exists in memory*/
				/*S user or system used*/
				/*TYPE	subtype*/
	char	gextra;/*G D/B L AVL limit_high(4)*/
			/*G 1 BYTE or 4KB*/
			/*D(=1for code)/B(=0for stack)	default operand size or stack pointer size or upper bound*/
			/*L	for 64-bit CPU.32-bit ,set to 0*/
			/*AVL	not used.Reserved for operating system,CPU will not use it*/
	char	base_high;
}segment_discriptor;

#define SEG_TYPE(seg)	((seg).privilage & 0x0f)
#define SEG_DPL(seg)	((seg).privilage & 0x60)
#define SEG_S(seg)	((seg).privilage & 0x10)
#define SEG_P(seg)	((seg).privilage & 0x80)
#define SEG_LIMIT(seg)	(((seg).gextra << 16) &	((seg).limit_low))
#define SEG_BASE(seg)	(\
	((seg).base_high << 24) & \
	((seg).base_mid  << 16) & \
	((seg).base_low ))

/**
 *an example
 *
 *0x00007c00 --> base
 *0x001FF    --> limit
 *G = 0		1 byte
 *S = 1		user
 *D = 1		32-bit segment
 *P = 1		in memory
 *L = 0		always
 *DPL = 0	r0
 *TYPE = 1000 	execute only
 *
 *
 */

//=============define functions============
//=====System kernel core functions=======
void enable_A20();
void reboot();
void load_gdtr(gdtr* pgdtr);

#endif /*END this file*/






