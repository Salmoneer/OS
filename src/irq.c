#include "irq.h"
#include "isr.h"
#include "idt.h"
#include "vga.h"
#include "pic.h"
#include "io.h"

void int32() { /* Timer */

}

void int33() { /* Keyboard Handler */
	terminal_print("KEYBOARD IRQ CALLED!!!!1!");
	PIC_send_eoi(1);
	unsigned char char_code = inportb(0x60);
	terminal_putc(char_code);
}

void int34(){}
void int35(){}
void int36(){}
void int37(){}
void int38(){}
void int39(){}
void int40(){}
void int41(){}
void int42(){}
void int43(){}
void int44(){}
void int45(){}
void int46(){}
void int47(){}
