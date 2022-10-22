[bits 16]

section .text

global _start
_start:
	mov ax, 0x1000
	mov es, ax
	mov ah, 0x02
	mov al, [READ_SECTORS]
	mov bx, 0
	mov cl, 2
	mov ch, 0
	mov dh, 0
	int 13h

	in al, 0x92
	or al, 2
	out 0x92, al

	cli

	xor ax, ax
	mov ds, ax

	lgdt [gdt_desc]

	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp 0x08:enter32

	jmp $

[bits 32]
enter32:
	mov ax, 0x10
	mov ds, ax

	jmp 0x08:0x10000
	
	mov byte [ds:0B8000h], 'E'
	mov byte [ds:0B8001h], 0x40

gdt:                    ; Address for the GDT
gdt_null:               ; Null Segment
        dd 0
        dd 0

gdt_code:               ; Code segment, read/execute, nonconforming
        dw 0x0FFFF
        dw 0
        db 0
        db 0b10011010
        db 0b11001111
        db 0

gdt_data:               ; Data segment, read/write, expand down
        dw 0x0FFFF
        dw 0
        db 0
        db 0b10010010
        db 0b11001111
        db 0

gdt_end:                ; Used to calculate the size of the GDT



gdt_desc:                       ; The GDT descriptor
        dw gdt_end - gdt - 1    ; Limit (size)
        dd gdt                  ; Address of the GDT

READ_SECTORS:
	db 0x80

times 510 - ( $ - $$ ) db 0
dw 0xaa55
