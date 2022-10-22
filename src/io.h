#ifndef IO_H
#define IO_H

#include <stdint.h>

void outportb(uint16_t port, uint8_t data);
void outportw(uint16_t port, uint16_t data);

uint8_t inportb(uint16_t port);
uint16_t inportw(uint16_t port);

void io_wait(void);

#endif
