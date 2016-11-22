# 1 "test.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "test.c"
# 15 "test.c"
int main()
{
 __asm__ __volatile__( "lmsw   %%ax \n\t" "ljmp   $" "0x100" ", $" "0x234" " \n\t" : :"a"(0x0001) :);
 return 0;
}
