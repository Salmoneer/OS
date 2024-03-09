ASM=nasm
LD=i686-elf-ld
CC=i686-elf-gcc --sysroot=../sysroot

ARCH=i386
KERNEL_ARCH_DIR=arch/$(ARCH)

include $(KERNEL_ARCH_DIR)/make.config

CCFLAGS=-std=gnu99 -O2 -g -ffreestanding -Iinclude -isystem '=/usr/include/' -iquote '=/usr/include/' -L '=/usr/lib/' -Wall -Wextra -nostdlib

KERNEL_OBJS=kernel/kernel.o $(KERNEL_ARCH_OBJS)

OBJS=$(KERNEL_OBJS)

.SUFFIXES: .c .asm .o

.PHONY: clean

all: clean kernel.bin

kernel.bin: $(OBJS) $(KERNEL_ARCH_DIR)/link.ld
	$(CC) -T $(KERNEL_ARCH_DIR)/link.ld -o $@ $(CCFLAGS) $(KERNEL_OBJS) -lk -lgcc

.asm.o:
	$(ASM) -f elf32 $< -o $@

.c.o:
	$(CC) -MD -c $< -o $@ $(CCFLAGS) -lk -lgcc

clean:
	rm -f kernel.bin
	find . \( -name '*.o' -or -name '*.d' \) -delete

-include $(OBJS:.o=.d)
