#include "keyboard.h"
#include "io.h"
#include "pic.h"
#include "stdio.h"
#include "vga.h"
#include <stdbool.h>

bool shift = false;

char keyboard_layout[2][128] = {{
0,   27,  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 127,
'\t','q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']','\n',
0,   'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'','`',
0,   '\\','z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
0,0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{
0,   27,  '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 127,
'\t','Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
0,   'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~',
0,   '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
0,0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

void keyboard_init() {
	outportb(0x60, 0xf4);
}

void keyboard_int_handler() {
	PIC_send_eoi(1);
	uint8_t scancode = inportb(0x60);
	if (scancode == 0x2a)
		shift = true;
	else if (scancode == 0xaa)
		shift = false;
	else if (scancode == 0x0e)
		terminal_backspace();
	else if (!(scancode & 0x80))
		kprintf("%c", keyboard_layout[shift][scancode]);
	
	if (scancode == 0x1c)
		kprintf("> ");
}
