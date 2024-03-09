ASM = nasm
CC = i686-elf-gcc --sysroot=../sysroot

CCFLAGS = -std=gnu99 -O2 -ffreestanding -Iinclude -isystem '=/usr/include/' -iquote '=/usr/include/' -L '=/usr/lib/' -Wall -Wextra -nostdlib


ARCH = i386
KERNEL_ARCH_DIR = arch/$(ARCH)

LINKER_CONFIG = $(KERNEL_ARCH_DIR)/link.ld


BUILD_DIR = ./build

include $(KERNEL_ARCH_DIR)/make.config
KERNEL_GLOBAL_OBJS = kernel/kernel.o
KERNEL_ALL_OBJS = $(KERNEL_GLOBAL_OBJS) $(KERNEL_ARCH_OBJS)

KERNEL = kernel.bin
KERNEL_OBJS = $(KERNEL_ALL_OBJS:%=$(BUILD_DIR)/%)
KERNEL_DEPS = $(KERNEL_OBJS:.o=.d)


.PHONY: clean

all: clean $(KERNEL)

$(KERNEL): $(KERNEL_OBJS) $(LINKER_CONFIG)
	$(CC) $(CCFLAGS) -T $(LINKER_CONFIG) $(KERNEL_OBJS) -o $@ -lk -lgcc

build/%.o: %.asm
	mkdir -p $(@D)
	$(ASM) -f elf32 $< -o $@

build/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CCFLAGS) -c $< -MMD -MP -o $@ -lk -lgcc

clean:
ifneq ($(wildcard $(KERNEL)),)
	rm $(KERNEL)
endif
ifneq ($(wildcard $(BUILD_DIR)),)
	rm -r $(BUILD_DIR)
endif

-include $(KERNEL_DEPS)
