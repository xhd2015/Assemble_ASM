.code16
.global _write_video_ram
.text
/*
*
*video buffer is at 0xb800:0x0000 (in character mode)
*
*/
_write_video_ram:
        push %ds
        mov $0xb800,%ax
        mov %ax,%ds
        mov $0x58,%al
        #mov 'X' to ram
        mov %al,%ds:0
        pop %ds
        ret

