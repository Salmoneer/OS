#include <stdio.h>

#if defined (__is_libk)
#include <kernel/tty.h>
#endif

int putchar(char c) {
#if defined (__is_libk)
	terminal_putc(c);
	return c;
#endif
}
