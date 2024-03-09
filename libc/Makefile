LD=i686-elf-gcc
CC=i686-elf-gcc

CCFLAGS=-std=gnu11 -O2 -g -ffreestanding -Wall -Wextra -nostdlib -I include -I ../kernel/include -D __is_libk

OBJS=stdio/printf.o stdio/putchar.o stdio/puts.o

.SUFFIXES: .c .o

all: clean libk.a install

libk.a: $(OBJS)
    $(AR) -crs $@ $(OBJS)

.c.o:
    $(CC) -MD -c $< -o $@ $(CCFLAGS)

install:
    mkdir -p ../sysroot/usr/include
    cp -r include/. ../sysroot/usr/include/.
    mkdir ../sysroot/usr/lib
    cp libk.a ../sysroot/usr/lib/

clean:
    rm -rf ../sysroot
    rm -f libk.a
    find . \( -name '*.o' -or -name '*.d' \) -delete

-include $(OBJS:.o=.d)
