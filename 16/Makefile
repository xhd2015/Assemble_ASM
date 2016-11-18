

TARGET_FILE=${FILE}
#DOSIMG=~/Downloads/bochs-imgs/odin1440.img
.PHONY :  com one_step cp_new_com view_code debug mount_img umount_img



one_step:com cp_new_com view_code

#you must put $$ to get a shell variable
debug:
	@echo ${SHELL}
	@echo ${FILE}
	@echo $$TARGET_FILE
	@echo ${TARGET_FILE}
	@echo $(TARGET_FILE)	
open_dos:
	qemu-system-i386 -fda ${DOSIMG}
mount_img:
	cd ~/asm/16
	source ~/xdir/.utils
	mysu mount ${DOSIMG} IMG
umount_img:
	cd ~/asm/16
	source ~/xdir/.utils
	mysu umount IMG
	

view_code: ${TARGET_FILE}
	objdump -d -m i8086 ${TARGET_FILE}

#if not one shell,they will be aparted from each other
.ONESHELL:
cp_new_com:
	cd ~/asm/16
	source ~/xdir/.utils
	mysu mount ${DOSIMG} IMG
	mysu rm IMG/${TARGET_FILE}.com
	mysu cp ${TARGET_FILE}.com IMG
	mysu umount IMG


com:${TARGET_FILE}.com

${TARGET_FILE}.com:${TARGET_FILE}
	objcopy -j .text -O binary ${TARGET_FILE} ${TARGET_FILE}.com

${TARGET_FILE}:${TARGET_FILE}.o
	ld -Ttext 0x100 -o ${TARGET_FILE} ${TARGET_FILE}.o

${TARGET_FILE}.o:${TARGET_FILE}.s
	as ${TARGET_FILE}.s -o ${TARGET_FILE}.o

clean:
	rm ${TARGET_FILE} ${TARGET_FILE}.o ${TARGET_FILE}.com
