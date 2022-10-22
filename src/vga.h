#ifndef VGA_H
#define VGA_H

#include <stddef.h>
#include <stdint.h>

void terminal_initialize();
void terminal_putc(char c);
void terminal_print(const char* str);

#endif
