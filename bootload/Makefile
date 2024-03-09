ASM=nasm

BOOTLOAD_SRCS=$(wildcard *.asm)
BOOTLOAD=bootload.bin

.PHONY: clean

all: clean bootload

bootload: $(BOOTLOAD_SRCS)
    $(ASM) -f bin $^ -o $(BOOTLOAD)

clean:
    rm -rf *.bin
