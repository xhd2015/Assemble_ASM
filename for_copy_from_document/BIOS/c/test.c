#define _STRING(x) #x
#define STRING(x) _STRING(x)
#define START_PROTECTED_MODE(new_seg,new_off) \
__asm__ __volatile__(\
        "lmsw   %%ax \n\t"\
        "ljmp   $" STRING(new_seg) ", $" STRING(new_off) " \n\t"\
        :\
        :"a"(0x0001)\
        :)

int main()
{
	START_PROTECTED_MODE(0x100,0x234);	
	return 0;
}
