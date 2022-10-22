#include <stdint.h>
#include "io.h"

void outportb(uint16_t port, uint8_t data) {
	asm volatile("outb %0, %1" : : "a"(data), "d"(port));
}

void outportw(uint16_t port, uint16_t data) {
	asm volatile("outw %0, %1" : : "a"(data), "d"(port));
}

uint8_t inportb(uint16_t port) {
	uint8_t ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
	return ret;
}

uint16_t inportw(uint16_t port) {
	uint16_t ret;
	asm volatile("inw %1, %0" : "=a"(ret) : "d"(port));
	return ret;
}

void io_wait(void) {
	outportb(0x80, 0);
}
