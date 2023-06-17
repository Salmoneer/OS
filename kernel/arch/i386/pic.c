#include <kernel/pic.h>
#include <kernel/io.h>

void pic_send_eoi(uint8_t irq) {
	if (irq >= 8)
		outb(PIC_SLAVE, PIC_EOI);
	outb(PIC_MASTER, PIC_EOI);
}

void pic_remap(int offset1, int offset2) {
	uint8_t mm, sm;

	mm = inb(PIC_MASTER);
	io_wait();
	sm = inb(PIC_SLAVE);
	io_wait();

	pic_send_eoi(15);
	io_wait();

	outb(PIC_MASTER, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC_SLAVE,  ICW1_INIT | ICW1_ICW4);
	io_wait();
	
	outb(PIC_MASTER_DATA, offset1);
	io_wait();
	outb(PIC_SLAVE_DATA,  offset2);
	io_wait();

	outb(PIC_MASTER_DATA, 4);
	io_wait();
	outb(PIC_SLAVE_DATA, 2);
	io_wait();

	outb(PIC_MASTER_DATA, ICW4_8086);
	io_wait();
	outb(PIC_SLAVE_DATA, ICW4_8086);
	io_wait();

	outb(PIC_MASTER_DATA, mm);
	io_wait();
	outb(PIC_SLAVE_DATA, sm);
	io_wait();
}

void pic_irq_enable(uint8_t interrupt) {
	uint16_t port;
	uint8_t value;

	if(interrupt < 8) {
		port = PIC_MASTER_DATA;
	} else {
		port = PIC_SLAVE_DATA;
		interrupt -= 8;
	}

	value = inb(port) | (1 << interrupt);
	outb(port, value);
}

void pic_irq_disable(uint8_t interrupt) {
	uint16_t port;
	uint8_t value;

	if(interrupt < 8) {
		port = PIC_MASTER_DATA;
	} else {
		port = PIC_SLAVE_DATA;
		interrupt -= 8;
	}

	value = inb(port) & ~(1 << interrupt);
	outb(port, value);
}
