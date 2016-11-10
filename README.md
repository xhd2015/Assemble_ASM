# Assemble_ASM
Exporting assemble language under linux by writing ASM files  and run it.

# Navigation
You read README.md at first,then decide which file you want to go.

# Introduction
All those .s files represent ASM files(written in AT&T style).And all of them are written,complied,ran under linux.The tools/command I used to do that are:
	[writing] [ use emacs ]
		$ASFILE=linux_exit
		$emacs $ASFILE.s
	[compiling] [ use as ]
		$as --64 -g -o $ASFILE.o $ASFILE.s
	[linking] [ use ld ]
		$ld -o $ASFILE $ASFILE.o
	[running]
		$./$ASFILE
	[debugging][ use ddd ]
		$ddd $ASFILE
	[other utilities][ including binutils]
		objdump,objcopy,readelf , etc.

# Which file to read?
There are mainly 3 types of file under this project: .s , .o and executeable
.s files are the source code file but more than source code.Actually , they are documented source files.Take /linux_exit_32.s for example,I firstly write this file mainly to test the Linux System Call : Exit- 0x80:0x4.So it's name is linux_exit_32.s.But soon I do more thing than that,say,I wrote a function named int_80_print,and debugged it and documented it.Then , there went all the left part of this file , I wrote one ,debugged one and documented one, one after one.
So all of this project , it's value lies in the documented file.You may want to read them and make yourself understood.


# Which file to get?
Other two type of files were uploaded because of the completeness.You can download them to compare with your compiled ones.

# The complete command
$ SF=linux_exit_32;as --64 -g -o ${SF}.o ${SF}.s ; ld  ${SF}.o -o ${SF} ;objdump -dx ${SF}
$ ddd $SF
