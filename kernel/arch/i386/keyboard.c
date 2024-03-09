#include <drivers/keyboard.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <kernel/io.h>

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
    inb(0x60);
}

void keyboard_interrupt() {
    uint8_t scancode = inb(0x60);
    if (scancode == 0x2a)
        shift = true;
    else if (scancode == 0xaa)
        shift = false;
    else if (!(scancode & 0x80))
        putchar(keyboard_layout[shift][scancode]);
}
