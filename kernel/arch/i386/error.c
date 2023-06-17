#include <kernel/io.h>
#include <stdio.h>

void panic(char *error_msg) {
	printf("\n\nFATAL ERROR: ");
	printf(error_msg);
	printf("\nSYSTEM HALTED");
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