__asm__(".code16gcc\n");
// if you want to run them in dos , or as bios program
//

#define VIDEO_RAM_ADDR 0xb800
void write_video_ram(char ch);

__asm__ (
".global _start\n\t"
".text\n\t"
"_start:\n\t"
"ljmp $0x7c0,$here\n\t"
"here:\n\t"
"mov %cs,%ax\n\t"
"mov %ax,%ds\n\t"
"mov %ax,%es\n\t"
"mov $stack,%eax\n\t"
"mov %eax,%esp\n\t"
"pushl $0\n\t"
"pushl $0\n\t"
"calll main\n\t"
"addl $8,%esp\n\t"
"die:\n\t"
"jmp die\n\t"
);

int main(int argc,char* argv[])
{
	write_video_ram('X');
	return 0;

}

void write_video_ram(char ch)
{
	__asm__ __volatile__ (
				"pushw %%es\n\t"
				"mov %%ax,%%es\n\t"
				"mov $0,%%ebx\n\t"
				"movb %%cl,%%es:(%%ebx)\n\t"
				"popw %%es\n\t"
				:
				:"a"(VIDEO_RAM_ADDR),"c"(ch)
				:"ebx");
		//if using es without __volatile__,error says unknown register name ‘es’ in ‘asm’

}
__asm__(".org 505\n\t"
	"stack:\n\t");
__asm__(".org 510\n\t"
	".word 0xAA55\n\t");
/*
 *
 *
 *
 *
 *You might have noticed that here I’ve used asm and __asm__. Both are valid. We can use __asm__ if the keyword asm conflicts with something in our program. 
 *
 *
 *
 *
 *
 *
 *
 *
<a href="http://www.cnblogs.com/openix/archive/2012/04/16/2451698.html">A Ref</a>
 */
/**
 *
 *#D <a href="http:/ /ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html#s3">The gcc inline asm introduction</a>
 *         asm ("cld\n\t"
 *              "rep\n\t"
 *              "stosl"
 *               :  no output registers 
             	 : "c" (count), "a" (fill_value), "D" (dest)
                 : "%ecx", "%edi");
 *
 *
 
+---+--------------------+
| r |    Register(s)     |
+---+--------------------+
| a |   %eax, %ax, %al   |
| b |   %ebx, %bx, %bl   |
| c |   %ecx, %cx, %cl   |
| d |   %edx, %dx, %dl   |
| S |   %esi, %si        |
| D |   %edi, %di        |
+---+--------------------+

asm("sidt %0\n" : :"m"(loc));

 */
