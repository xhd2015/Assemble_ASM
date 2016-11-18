	.code16
	.arch i8086,nojumps
	.global _set_cursor_position , _get_cursor_position,_exit_to_dos
	.global _read_char,_put_char,_get_str,_print_str
	.global _start
	.text
	jmp _start
	
str:	.string "Hello My Sonxxxxxx","$"
_start:
	mov %cs,%ax
	mov %ax,%ds
	mov %ax,%ss
	mov %ax,%es
	
	mov $stack,%ax
	mov %ax,%sp

	mov $str,%dx
	call _print_str
	
	#seek for BIOS info
	mov $0,%si
	mov $100,%cx
	mov $buf,%dx
__load_print_bios:
	push %ds
	mov $0xFFFF,%ax
	mov %ax,%ds
	call _cp_from_mem
	pop %ds
	
	call _print_str
	loop __load_print_bios
	
	
	mov $0x24,%dl #'$'
	call _put_char
	
	
	mov $0xF1,%al #failed
	call _exit_to_dos
_set_cursor_position:	#int_10(ah==2,bh=page_number:=0,dh=x,dl=y)
	mov $2,%ah
	int $0x10
	ret
_get_cursor_position:	#dh:x,dl:y -- int_10(ah==3,bh=page_number:=0)
	mov $0x3,%ah
	int $0x10
	ret
_exit_to_dos:	#int_21(ah==4c,al=code)
	mov $0x4c,%ah
	int $0x21
_read_char:	#al -- int_21(ah=1)
	mov $0x1,%ah
	int $0x21
	ret
_put_char:	#int_21(ah=2,dl=char)
	mov $0x2,%ah
	int $0x21
	ret
_get_str: # -- int_21(ah==0xa,ds:dx=addr) -- until enter pressed
	#the map of addr should be
	#	[maxlen_of_buffer]  [actual_input_len] ...  [0D] -- 0D means \n
	mov $0xa,%ah
	int $0x21
	ret
_cp_from_mem:	# -- cp(ds:si-->es:di:=buf)
	cld
	push %cx
	mov $buf_len-1,%cx
	mov $buf,%di
	
	mov $0x24,%al
	mov %al,%es:buf_len(%di) #$--->last
	rep movsb #cx times repeat
	pop %cx
	
	ret

	
_print_str:	#int_21(ah==9,ds:dx=target_ending_with_$)
	# end with $,not \0, say _print_str("hello","$")
	mov $0x9,%ah
	int $0x21
	ret
	.org 0x200
buf:
buf_len = 32
	.org 0xfff
stack:	
