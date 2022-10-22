ASM=nasm
LD=i686-elf-ld
CC=i686-elf-gcc

CCFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

KERNEL_ASM_SRCS=$(filter-out $(BOOTLOAD_SRCS), $(wildcard src/*.asm))
KERNEL_C_SRCS=$(wildcard src/*.c)
KERNEL_OBJS=$(KERNEL_C_SRCS:.c=.o) $(KERNEL_ASM_SRCS:.asm=.o)

BOOTLOAD_SRCS=src/bootload.asm
BOOTLOAD_OBJS=$(BOOTLOAD_SRCS:.asm=.o)

BOOTLOAD=bootload.bin
KERNEL=kernel.bin

all: bootload kernel build

clean:
	rm ./src/*.o
	rm ./*.flp
	rm ./bin/*.bin

%.o: %.asm
	$(ASM) -f elf32 -o $@ $<

%.o: %.c
	$(CC) -c $< -o $@ $(CCFLAGS)

bootload: $(BOOTLOAD_OBJS)
	$(LD) -o ./bin/$(BOOTLOAD) $^ -Ttext 0x7C00 --oformat=binary

kernel: $(KERNEL_OBJS)
	$(CC) -Tsrc/link.ld -ffreestanding -O2 -nostdlib -o ./bin/$(KERNEL) $^ -lgcc

build: bootload kernel
	dd if=bin/bootload.bin of=boot.flp bs=512 seek=0 &> /dev/null
	dd if=bin/kernel.bin   of=boot.flp bs=512 seek=1 &> /dev/null
