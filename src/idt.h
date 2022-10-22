#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define INT_OPTS_R0 0x8E
#define INT_OPTS_R3 0xEE

typedef struct {
	uint16_t offset_low;
	uint16_t selector;
	uint8_t zero;
	uint8_t settings;
	uint16_t offset_high;
} __attribute__ ((packed)) interrupt;

typedef struct {
	uint16_t limit;
	interrupt *base;
} __attribute__ ((packed)) idtr;

void loadIDTR();
void add_interrupt(int number, void (*handler)());

#endif
