#include "idt.h"
#include "vga.h"

idtr IDTR;
interrupt IDT[256];

void loadIDTR()
{
	IDTR.limit  = 256*(sizeof(interrupt)-1);
	IDTR.base   = IDT;

    asm volatile("LIDT (%0) ": :"g" (IDTR));
}

void add_interrupt(int number, void (*handler)())
{
	 uint16_t selector = 0x08;
     uint32_t offset = (uint32_t)handler;

     asm volatile("movw %%cs,%0" :"=g"(selector));

	 IDT[number].offset_low   = (offset & 0xFFFF);
	 IDT[number].selector     = selector;
	 IDT[number].settings     = INT_OPTS_R0;
     IDT[number].offset_high  = (offset >> 16);
	 IDT[number].zero         = 0;
}
