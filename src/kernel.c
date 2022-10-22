#include "vga.h"
#include "isr.h"
#include "idt.h"
#include "irq.h"
#include "pic.h"
#include "error.h"

void kernel_main() {
	asm volatile("cli");
	remap_PIC(32, 40);
	load_exceptions();
	loadIDTR();
	outportb(0x21, 0xfd);
	outportb(0xa1, 0xff);
	asm volatile("sti");
	terminal_initialize();
	terminal_print("Hello, there\n");
}
