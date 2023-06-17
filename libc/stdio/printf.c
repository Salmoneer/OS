#include <stdio.h>

#include <stdarg.h>

char* convert(unsigned int num, int base)
{ 
    static char rep[16]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr;

    ptr = &buffer[49];
    *ptr = '\0';

    do { 
        *--ptr = rep[num%base];
        num /= base;
    } while(num != 0);

    return(ptr);
}

void printf(char *format, ...) {
	char *traverse;

	unsigned char i;
	int si;
	char *s;

	va_list arg;
	va_start(arg, format);

	for (traverse = format; *traverse != '\0'; traverse++) {
		while (*traverse != '%') {
			if (*traverse == '\0') return;
			putchar(*traverse);
			traverse++;
		}

		traverse++;

		switch (*traverse) {
			case 'c':
				i = va_arg(arg, int);
				putchar(i);
				break;

			case 's':
				s = va_arg(arg, char *);
				puts(s);
				break;

			case 'd':
				si = va_arg(arg, int);
				if (si < 0) {
					si = -1;
					putchar('-');
				}
				puts(convert(si, 10));
				break;

			case 'o':
				i = va_arg(arg, unsigned int);
				puts(convert(i, 8));
				break;

			case 'x':
				i = va_arg(arg, unsigned int);
				puts(convert(i, 16));
				break;

			default:
				putchar(*traverse);
				break;
		}
	}

	va_end(arg);
}
