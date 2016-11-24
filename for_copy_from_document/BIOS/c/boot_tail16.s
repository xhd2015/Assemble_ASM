	.file	"boot_tail.c"
#APP
	.global _stack 
	
	.global _idtm 
	
	.global _gdtm 
	
	.global _gdt 
	
	 
	_logical_zero_pos:
	 
	
	_gdt:
	.word 0,0,0,0 
	.word 0x07FF 
	.word 0x0000 
	.word 0x9A00 
	.word 0x00C0 
	.word 0x07FF 
	.word 0x0000 
	.word 0x9200 
	.word 0x00C0 
	
	 
	_gdtm:
	.word 0x07FF
	
	 
	
	.long _gdt+0x7c00
	
	 
	_idtm:
	.word 0
	
	 
	
	.long 0
	
	 
	
	.long _logical_zero_pos
	
	last_len = 350 
	
	.org 505-last_len
	_stack:
	 
	
	.org 510-last_len
	
	.word 0xAA55
	
	.ident	"GCC: (GNU) 6.2.1 20160916 (Red Hat 6.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
