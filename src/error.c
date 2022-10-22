#include "error.h"
#include "vga.h"
#include "idt.h"
#include "isr.h"
#include "pic.h"

void load_exceptions() {
	add_interrupt(0, intw0);
	add_interrupt(1, intw1);
	add_interrupt(2, intw2);
	add_interrupt(3, intw3);
	add_interrupt(4, intw4);
	add_interrupt(5, intw5);
	add_interrupt(6, intw6);
	add_interrupt(7, intw7);
	add_interrupt(8, intw8);
	add_interrupt(9, intw9);
	add_interrupt(10, intw10);
	add_interrupt(11, intw11);
	add_interrupt(12, intw12);
	add_interrupt(13, intw13);
	add_interrupt(14, intw14);
	add_interrupt(15, intw15);
	add_interrupt(16, intw16);
	add_interrupt(17, intw17);
	add_interrupt(18, intw18);
	add_interrupt(19, intw19);

	add_interrupt(32, intw32);
	add_interrupt(33, intw33);
	add_interrupt(34, intw34);
	add_interrupt(35, intw35);
	add_interrupt(36, intw36);
	add_interrupt(37, intw37);
	add_interrupt(38, intw38);
	add_interrupt(39, intw39);
	add_interrupt(40, intw40);
	add_interrupt(41, intw41);
	add_interrupt(42, intw42);
	add_interrupt(43, intw43);
	add_interrupt(44, intw44);
	add_interrupt(45, intw45);
	add_interrupt(46, intw46);
	add_interrupt(47, intw47);
}

void panic(char *error_msg) {
	terminal_print("\n\nFATAL ERROR: ");
	terminal_print(error_msg);
	terminal_print("\nSYSTEM HALTED");
	outportb(PIC_MASTER, PIC_EOI);
	asm volatile("cli\nhlt");
}

void int0() {
	panic("Divide by zero");
}

void int1() {
	panic("Debug");
}

void int2() {
	panic("NMI");
}

void int3() {
	panic("Breakpoint");
}

void int4() {
	panic("Overflow");
}

void int5() {
	panic("Bound Range Exceeded");
}

void int6() {
	panic("Invalid Opcode");
}

void int7() {
	panic("Coprocessor not Available");
}

void int8() {
	panic("Double Fault");
}

void int9() {
	panic("Coprocessor Segment Overrun");
}

void int10() {
	panic("Invalid TSS");
}

void int11() {
	panic("Segment not Present");
}

void int12() {
	panic("Stack Segment Fault");
}

void int13() {
	panic("General Protection Fault");
}

void int14() {
	panic("Page Fault");
}

void int15() {
	panic("RESERVED");
}

void int16() {
	panic("FPU Floating Point Error");
}

void int17() {
	panic("Alignment Check");
}

void int18() {
	panic("Machine Check");
}

void int19() {
	panic("SIMD Floating Point Exception");
}
