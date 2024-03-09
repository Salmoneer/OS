ASM=nasm

BOOTLOAD=bootload.bin
BOOTLOAD_SRCS=$(wildcard *.asm)

.PHONY: clean

all: clean $(BOOTLOAD)

$(BOOTLOAD): $(BOOTLOAD_SRCS)
	$(ASM) -f bin $^ -o $(BOOTLOAD)

clean:
	rm -rf $(BOOTLOAD)
