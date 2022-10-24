#include "irq.h"
#include "isr.h"
#include "idt.h"
#include "stdio.h"
#include "pic.h"
#include "io.h"
#include "keyboard.h"

void int32() { /* Timer */

}

void int33() { /* Keyboard Handler */
	keyboard_int_handler();
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
