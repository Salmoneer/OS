#include "vga.h"

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

const size_t VGA_COLS = 80;
const size_t VGA_ROWS = 25;

size_t terminal_row = 0;
size_t terminal_col = 0;
uint8_t terminal_color = 0x0f;

void terminal_initialize() {
	for (size_t col = 0; col < VGA_COLS; col++) {
		for (size_t row = 0; row < VGA_ROWS; row++) {
				size_t index = col + row * VGA_COLS;
				vga_buffer[index] = ((uint16_t)terminal_color << 8) | ' ';
		}
	}
}

void terminal_scroll(const uint8_t lines) {
	for (size_t col = 0; col < VGA_COLS; col++) {
		for (size_t row = 0; row < VGA_ROWS; row++) {
			size_t index = col + row * VGA_COLS;
			if (row < VGA_COLS-lines)
				vga_buffer[index] = vga_buffer[index+(lines*VGA_COLS)];
			else
				vga_buffer[index] = ((uint16_t)terminal_color << 8) | ' ';
		}
	}
}

void terminal_putc(char c) {
	if (c == '\n') {
		terminal_row++;
		terminal_col = 0;
	}
	else {
		const int index = (VGA_COLS * terminal_row) + terminal_col;
		vga_buffer[index] = ((uint16_t)terminal_color << 8) | c;
		terminal_col++;
	}
	if (terminal_col >= VGA_COLS) {
		terminal_row++;
		terminal_col = 0;
	}
	if (terminal_row > VGA_ROWS) {
		terminal_col = 0;
		terminal_scroll(1);
	}
}

void terminal_print(const char* str) {
	for (size_t i = 0; str[i] != '\0'; i++) {
		terminal_putc(str[i]);
	}
}
