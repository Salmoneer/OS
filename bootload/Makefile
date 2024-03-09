ASM = nasm

BOOTLOAD = bootload.bin
BOOTLOAD_SRCS = $(wildcard *.asm)


.PHONY: clean

all: clean $(BOOTLOAD)

$(BOOTLOAD): $(BOOTLOAD_SRCS)
	$(ASM) -f bin $^ -o $@

clean:
ifneq ($(wildcard $(BOOTLOAD)),)
	rm $(BOOTLOAD)
endif
