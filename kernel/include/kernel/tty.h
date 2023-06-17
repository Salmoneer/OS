#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stdint.h>

void terminal_initialize(void);
void terminal_move_cursor(void);
void terminal_scroll(const uint8_t lines);
void terminal_putc(char c);
void terminal_print(const char* str);

#endif
