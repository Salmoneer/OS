#include <stddef.h>

#include "vga.h"

static uint16_t* VGA_MEMORY = (uint16_t*)0xB8000;

static const size_t VGA_COLS = 80;
static const size_t VGA_ROWS = 25;

static size_t terminal_row;
static size_t terminal_col;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize() {
	terminal_row = 0;
	terminal_col = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GRAY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t col = 0; col < VGA_COLS; col++) {
		for (size_t row = 0; row < VGA_ROWS; row++) {
				size_t index = col + row * VGA_COLS;
				terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

/*void terminal_move_cursor() {
	size_t index = terminal_row * VGA_COLS + terminal_col;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (index & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((index >> 8) & 0xFF));
}*/

void terminal_scroll(const uint8_t lines) {
	for (size_t col = 0; col < VGA_COLS; col++) {
		for (size_t row = 0; row < VGA_ROWS; row++) {
			size_t index = col + row * VGA_COLS;
			if (row < VGA_ROWS-lines)
				terminal_buffer[index] = terminal_buffer[index+(lines*VGA_COLS)];
			else
				terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	terminal_col = 0;
	terminal_row -= lines;
}

void terminal_putc(char c) {
	if (c == '\n') {
		terminal_row++;
		terminal_col = 0;
	} else {
		const int index = (VGA_COLS * terminal_row) + terminal_col;
		terminal_buffer[index] = vga_entry(c, terminal_color);
		terminal_col++;
		//terminal_move_cursor();
	}

	if (terminal_col >= VGA_COLS) {
		terminal_row++;
		terminal_col = 0;
	}

	if (terminal_row >= VGA_ROWS) {
		terminal_col = 0;
		terminal_scroll(1);
	}
}

void terminal_print(const char* str) {
	for (size_t i = 0; str[i] != '\0'; i++) {
		terminal_putc(str[i]);
	}
}
