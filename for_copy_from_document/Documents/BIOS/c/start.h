
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
"call main\n\t"
"addl $8,%esp\n\t"
"die:\n\t"
"jmp die\n\t"
);

