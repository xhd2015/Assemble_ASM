000fe1fb: (                    ): mov ax, 0xc780            ; b880c7
000fe1fe: (                    ): call .-16133              ; e8fbc0
000fe201: (                    ): call .+12223              ; e8bf2f
000fe204: (                    ): call .-19197              ; e803b5
000fe207: (                    ): call .-19065              ; e887b5
000fe20a: (                    ): call .+13875              ; e83336
000fe20d: (                    ): call .+14741              ; e89539
000fe210: (                    ): call .+21497              ; e8f953
000fe213: (                    ): call .+12294              ; e80630
000fe216: (                    ): mov cx, 0xc800            ; b900c8
000fe219: (                    ): mov ax, 0xe000            ; b800e0
000fe21c: (                    ): call .-16163              ; e8ddc0
000fe21f: (                    ): call .+12662              ; e87631
000fe222: (                    ): sti                       ; fb
000fe223: (                    ): int 0x19                  ; cd19
000000000000000000000000000000000000000000000000000000000000000000000
<a href="http://stackoverflow.com/questions/15627668/why-does-the-bios-int-0x19-load-bootloader-at-0x7c00">a reference</a>
As we know the BIOS Interrupt (INT) 0x19 which searches for a boot signature (0xAA55). Loads and executes our bootloader at 0x7C00 if it found.

000fe6f2: (                    ): jmp .-20487               ; e9f9af
000fe6f5: (                    ): or byte ptr ds:[bx+si], al ; 0800
000fe6f7: (                    ): cld                       ; fc
000fe6f8: (                    ): add byte ptr ds:[bx+di], al ; 0001
000fe6fa: (                    ): jz .+64                   ; 7440
000000000000000000000000000000000000000000000000000000000000000000000
This is exactly what the int 0x19 does.Let's explain it.
jmp . - 20487  that is set eip=0xe6f2+2-20487=38637=0x96ee

000f96ee: (                    ): push bp                   ; 55
000f96ef: (                    ): mov bp, sp                ; 89e5
000f96f1: (                    ): mov ax, 0xfffe            ; b8feff
000f96f4: (                    ): mov sp, ax                ; 89c4
000f96f6: (                    ): xor ax, ax                ; 31c0
000f96f8: (                    ): mov ss, ax                ; 8ed0
000f96fa: (                    ): mov bx, 0x9ff0            ; bbf09f
000f96fd: (                    ): mov ds, bx                ; 8edb
000f96ff: (                    ): mov word ptr ds:0x0082, ax ; a38200
000f9702: (                    ): mov ds, ax                ; 8ed8
000f9704: (                    ): push ax                   ; 50
000f9705: (                    ): call .-2029               ; e813f8
----------- start at here, 'Hello World' is print
000f9708: (                    ): int 0x18                  ; cd18
000f970a: (                    ): xor ax, ax                ; 31c0
000f970c: (                    ): mov ds, ax                ; 8ed8
000f970e: (                    ): mov al, 0x00              ; b000
000f9710: (                    ): mov byte ptr ds:0x043e, al ; a23e04
000f9713: (                    ): mov byte ptr ds:0x043f, al ; a23f04
000f9716: (                    ): mov byte ptr ds:0x0440, al ; a24004
000f9719: (                    ): mov byte ptr ds:0x0441, al ; a24104
000f971c: (                    ): mov byte ptr ds:0x0442, al ; a24204
000f971f: (                    ): mov byte ptr ds:0x0443, al ; a24304
000f9722: (                    ): mov byte ptr ds:0x0444, al ; a24404
000f9725: (                    ): mov byte ptr ds:0x0445, al ; a24504
000f9728: (                    ): mov byte ptr ds:0x0446, al ; a24604
000f972b: (                    ): mov byte ptr ds:0x0447, al ; a24704
000f972e: (                    ): mov byte ptr ds:0x0448, al ; a24804
000f9731: (                    ): mov byte ptr ds:0x048b, al ; a28b04
000f9734: (                    ): mov al, 0x10              ; b010
000f9736: (                    ): out 0x70, al              ; e670
000f9738: (                    ): in al, 0x71               ; e471
000f973a: (                    ): mov ah, al                ; 88c4
000f973c: (                    ): shr al, 0x04              ; c0e804
000f973f: (                    ): jz .+4                    ; 7404
000f9741: (                    ): mov bl, 0x07              ; b307
000f9743: (                    ): jmp .+2                   ; eb02
000f9745: (                    ): mov bl, 0x00              ; b300
000f9747: (                    ): mov al, ah                ; 88e0
000f9749: (                    ): and al, 0x0f              ; 240f
000f974b: (                    ): jz .+3                    ; 7403
000f974d: (                    ): or bl, 0x70               ; 80cb70
000f9750: (                    ): mov byte ptr ds:0x048f, bl ; 881e8f04
000f9754: (                    ): mov al, 0x00              ; b000
000f9756: (                    ): mov byte ptr ds:0x0490, al ; a29004
000f9759: (                    ): mov byte ptr ds:0x0491, al ; a29104
000f975c: (                    ): mov byte ptr ds:0x0492, al ; a29204
000f975f: (                    ): mov byte ptr ds:0x0493, al ; a29304
000f9762: (                    ): mov byte ptr ds:0x0494, al ; a29404
000f9765: (                    ): mov byte ptr ds:0x0495, al ; a29504
000f9768: (                    ): mov al, 0x02              ; b002
000f976a: (                    ): out 0x0a, al              ; e60a
000f976c: (                    ): mov ax, 0xefde            ; b8deef
000f976f: (                    ): mov word ptr ds:0x0078, ax ; a37800
000f9772: (                    ): mov ax, 0xf000            ; b800f0
000f9775: (                    ): mov word ptr ds:0x007a, ax ; a37a00
000f9778: (                    ): mov ax, 0xec59            ; b859ec
000f977b: (                    ): mov word ptr ds:0x0100, ax ; a30001
000f977e: (                    ): mov ax, 0xf000            ; b800f0
000f9781: (                    ): mov word ptr ds:0x0102, ax ; a30201
000f9784: (                    ): mov ax, 0xef57            ; b857ef
000f9787: (                    ): mov word ptr ds:0x0038, ax ; a33800
000f978a: (                    ): mov ax, 0xf000            ; b800f0
000f978d: (                    ): mov word ptr ds:0x003a, ax ; a33a00
000f9790: (                    ): ret                       ; c3
00000000000000000000000000000000000000000000000000000000000000000000
000f9791: (                    ): mov al, 0x0a              ; b00a



jz . + 64  that is set eip=0xe6fa+64=0xe73a


000fe73a: (                    ): pusha                     ; 60
000fe73b: (                    ): xor ax, ax                ; 31c0
000fe73d: (                    ): mov ds, ax                ; 8ed8
000fe73f: (                    ): call .+21683              ; e8b354
000fe742: (                    ): popa                      ; 61
000fe743: (                    ): pop ds                    ; 1f
000fe744: (                    ): iret                      ; cf
00000000000000000000000000000000000000000000000000000000000000000000
