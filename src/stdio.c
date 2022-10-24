#include "stdio.h"
#include "vga.h"
#include <stdarg.h>

char *convert(unsigned int num, int base) 
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 

    return(ptr); 
}

void kprintf(char *format, ...) {
	char *traverse;

	unsigned char i;
	int si;
	char *s;

	va_list arg;
	va_start(arg, format);

	for (traverse = format; *traverse != '\0'; traverse++) {
		while (*traverse != '%') {
			if (*traverse == '\0') return;
			terminal_putc(*traverse);
			traverse++;
		}

		traverse++;

		switch (*traverse) {
			case 'c':
				i = va_arg(arg, int);
				terminal_putc(i);
				break;

			case 's':
				s = va_arg(arg, char *);
				terminal_print(s);
				break;

			case 'd':
				si = va_arg(arg, int);
				if (si < 0) {
					si = -1;
					terminal_putc('-');
				}
				terminal_print(convert(si, 10));
				break;

			case 'o':
				i = va_arg(arg, unsigned int);
				terminal_print(convert(i, 8));
				break;

			case 'x':
				i = va_arg(arg, unsigned int);
				terminal_print(convert(i, 16));
				break;

			default:
				terminal_putc(*traverse);
				break;
		}
	}

	va_end(arg);
}
