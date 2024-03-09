#include <stdio.h>
#include <string.h>

int puts(const char* str) {
    int c = 0;
#if defined (__is_libk)
    for (size_t i = 0; str[i]!=0; i++) {
        putchar(str[i]);
        c++;
    }
#endif
    return c;
}
