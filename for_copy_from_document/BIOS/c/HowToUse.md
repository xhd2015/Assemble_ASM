# About
主要使用c语言改写了linux 0.11 bootsect.s的代码。其中一个主要改动是使用LBA读取读取扇区而非CHS。
另外，在编译过程生成超过了512字节的文件，导致.org 510 报错.其原因在于定义了太多函数，生成了不必要的信息，超出了长度限制。解决方案是使用宏代替函数。

# 编译，生成，执行
无论如何，现在只有bootsect.img文件，想要正常启动linux 0.11的内核，还需要head.img文件。

假设现在只有一个bootsect.c文件，需要将其编译成.img文件，然后载入BIOS.
所有需要的工具都是跨平台的，这些工具包括:
	gcc
	gas
	ld
	objcopy
	bochs
	make
windows下可以安装cygwin来使用这些工具，其他平台接近于Linux，可能很方便安装这些工具.

在命令行下,cd到此文件所在的目录,键入:
	make bootsect.s opt=pure-asm
来生成不带任何调试信息，没有任何优化的汇编源文件，这样的代码，除去堆栈框架之外，通常和手工编写的代码差别不大

生成.img文件:
	make bootsect.img opt=pure-asm
装入bochs虚拟机:
	首先配置.bochsrc文件，加入
		floppya:1_44=/home/Douglas/Documents/BIOS/c/bootsect.img,status=inserted
		boot: floopy
	然后使用bochs -q -f .bochsrc 运行，在0x7c00处开始调试即可。

# Why
可以查看a_summary_if**machenism 文件查看使用gcc生成汇编代码的详细信息。



