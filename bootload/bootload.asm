[bits 16]
[org 0x7c00]

; BIOS Parameter Block (BPB)
jmp short bootload_start
nop
BPBOEMLabeldb "BOOTDRIV"
BPBBytesPerSector       dw 512
BPBSectorsPerCluster    db 1
BPBReservedSectors      dw 1
BPBFATCount             db 2
BPBRootEntries          dw 224
BPBLogicalSectors       dw 3072
BPBMediaType            db 0xF0
BPBSectorsPerFAT        dw 9
BPBSectorsPerTrack      dw 64
BPBHeadsPerCylinder     dw 16
BPBHiddenSectors        dd 0
BPBTotalSectorsBig      dd 0

; Boot Record (BR)
BRDriveNumber           db 0
db 0
BRSignature             db 0x29
BRSerialNumber          dd 0x69420
BRVolumeLabel           db "BOOT DRIVE "
BRFileSystemType        db "FAT12   "

bootload_start:
; record disk number
    mov BYTE[BRDriveNumber], dl

; setup stack
    xor ax, ax
    cli
    mov ss, ax
    mov sp, 0x7c00
    sti

; reset disk
    xor ax, ax
    int 13h

; disable a20
    in al, 0x92
    or al, 2
    out 0x92, al

; init segment registers to 0
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    jmp 0x0000:load_root

load_root:
    xor cx, cx
    xor dx, dx
    mov ax, 32
    mul WORD[BPBRootEntries]
    div WORD[BPBBytesPerSector]
    xchg ax, cx

    mov al, BYTE[BPBFATCount]
    mul WORD[BPBSectorsPerFAT]
    add ax, WORD[BPBReservedSectors]
    mov WORD[DATASTART], ax
    add WORD[DATASTART], cx
    
    mov bx, 0x7e00
    call read

find_file:
    mov cx, WORD[BPBRootEntries]
    mov di, 0x7e00
.loop:
    push cx
    mov cx, 11
    mov si, LOAD_NAME
    push di
    rep cmpsb
    pop di
    je load_fat
    pop cx
    add di, 32
    loop .loop
    mov bx, FIND_FAIL
    call prints
    jmp $

load_fat:
    mov dx, WORD[di + 0x1a]
    mov WORD[CLUSTER], dx

    xor ax, ax
    mov al, BYTE[BPBFATCount]
    mul WORD[BPBSectorsPerFAT]
    mov cx, ax

    mov ax, WORD[BPBReservedSectors]

    mov bx, 0x7e00
    call read

    mov ax, 0x1000
    mov es, ax
    xor bx, bx
    push bx

load_file:
    mov ax, WORD[CLUSTER]
    pop bx
    call clustertolba
    xor cx, cx
    mov cl, BYTE[BPBSectorsPerCluster]
    call read
    add bx, WORD[BPBBytesPerSector]
    push bx

    mov ax, WORD[CLUSTER]
    mov cx, ax
    mov dx, ax
    shr dx, 1
    add cx, dx
    mov bx, 0x7e00
    add bx, cx
    mov dx, WORD[bx]
    test ax, 1
    jnz .odd

.even:
    and dx, 0b0000111111111111
    jmp .done

.odd:
    shr dx, 4

.done:
    mov WORD[CLUSTER], dx
    cmp dx, 0x0FFF
    jb load_file

    ; mov bx, STAT
    ; call prints

; load into 32 bit mode
    cli

    xor ax, ax
    mov ds, ax

    lgdt [gdt_desc]

    mov eax, cr0

    or eax, 1
    mov cr0, eax

; jump to 32 bit code
    jmp 0x08:enter32

    jmp $

; clustertolba
; IN:   AX: CLUSTER
; OUT:  AX: LBA
clustertolba:
    sub ax, 2
    xor cx, cx
    mov cl, BYTE[BPBSectorsPerCluster]
    mul cx
    add ax, WORD[DATASTART]
    ret

; lbatochs
; IN:   AX: LBA
; OUT:  CYLINDER, HEAD, SECTOR variables
lbatochs:
    xor dx, dx
    div WORD[BPBSectorsPerTrack]
    inc dl
    mov BYTE[SECTOR], dl

    xor dx, dx
    div WORD[BPBHeadsPerCylinder]
    mov BYTE[HEAD], dl

    mov BYTE[CYLINDER], al
    ret

; read
; IN:   AX:     LBA of first sector
; IN:   ES:BX:  Location to read to
; IN:   CX:     Number of sectors
; reads off disk at specified location
read:
    push ax
    push bx
.loop:
    push ax
    push bx
    push cx
    push dx

    call lbatochs

    mov ch, BYTE[CYLINDER]
    mov cl, BYTE[SECTOR]
    mov dh, BYTE[HEAD]
    mov dl, BYTE[BRDriveNumber]

    mov ah, 2
    mov al, 1

    int 13h
    jnc .success

    jmp $

.success:
    pop dx
    pop cx
    pop bx
    pop ax
    add bx, WORD[BPBBytesPerSector]
    inc ax
    loop .loop
    pop bx
    pop ax
    ret
    
; prints
; IN: BX: string pointer
; prints string

prints:
    push ax
    mov ah, 0x0e
.loop:
    mov al, BYTE[bx]
    inc bx
    cmp al, 0
    jz .done
    int 10h
    jmp .loop
.done:
    pop ax
    ret

[bits 32]
enter32:
    mov ax, 0x10
    mov ds, ax
    mov es, ax

    jmp 0x08:0x10000
    
    mov WORD[ds:0B8000h], 0x0445                    ; if jump to kernel fails, display a red 'E' in the top left
    jmp $

; DATA:

gdt:                                                ; Address for the GDT
gdt_null:                                           ; Null Segment
        dd 0
        dd 0

gdt_code:                                           ; Code segment, read/execute, nonconforming
        dw 0x0FFFF
        dw 0
        db 0
        db 0b10011010
        db 0b11001111
        db 0

gdt_data:                                           ; Data segment, read/write, expand down
        dw 0x0FFFF
        dw 0
        db 0
        db 0b10010010
        db 0b11001111
        db 0

gdt_end:



gdt_desc:                                           ; The GDT descriptor
    dw gdt_end - gdt - 1                            ; Length
    dd gdt                                          ; Address of the GDT


FIND_FAIL:    db "COULDN'T FIND "

LOAD_NAME:    db "KERNEL  BIN"

CYLINDER:     db 0
HEAD:         db 0
SECTOR:       db 0

CLUSTER:      dw 0

DATASTART:    dw 0

times 510 - ( $ - $$ ) db 0
dw 0xaa55
