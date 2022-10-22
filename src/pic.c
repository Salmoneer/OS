#include "pic.h"
#include "io.h"
#include <stdint.h>

void PIC_send_eoi(uint8_t irq) {
	if (irq >= 8)
		outportb(PIC_SLAVE, PIC_EOI);
	outportb(PIC_MASTER, PIC_EOI);
}

void remap_PIC(int offset1, int offset2) {
	uint8_t mm, sm;

	mm = inportb(PIC_MASTER);
	io_wait();
	sm = inportb(PIC_SLAVE);
	io_wait();

	PIC_send_eoi(15);
	io_wait();

	outportb(PIC_MASTER, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outportb(PIC_SLAVE,  ICW1_INIT | ICW1_ICW4);
	io_wait();
	
	outportb(PIC_MASTER_DATA, offset1);
	io_wait();
	outportb(PIC_SLAVE_DATA,  offset2);
	io_wait();

	outportb(PIC_MASTER_DATA, 4);
	io_wait();
	outportb(PIC_SLAVE_DATA, 2);
	io_wait();

	outportb(PIC_MASTER_DATA, ICW4_8086);
	io_wait();
	outportb(PIC_SLAVE_DATA, ICW4_8086);
	io_wait();

	outportb(PIC_MASTER_DATA, mm);
	io_wait();
	outportb(PIC_SLAVE_DATA, sm);
	io_wait();
}
