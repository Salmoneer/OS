AR = i686-elf-ar
CC = i686-elf-gcc

CCFLAGS = -std=gnu99 -O2 -ffreestanding -I include -I ../kernel/include -Wall -Wextra -nostdlib -D __is_libk

BUILD_DIR = ./build

SYSROOT = ../sysroot


LIBK = libk.a
LIBK_SRCS = $(wildcard **/*.c)
LIBK_OBJS = $(LIBK_SRCS:%.c=build/%.o)
LIBK_DEPS = $(LIBK_OBJS:.o=.d)


.PHONY: clean install

all: clean libk.a install

libk.a: $(LIBK_OBJS)
	$(AR) -crs $@ $(LIBK_OBJS)

build/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CCFLAGS) -MMD -c $< -o $@

install: $(LIBK)
	mkdir -p $(SYSROOT)/usr/lib
	cp -r include $(SYSROOT)/usr/
	cp $(LIBK) $(SYSROOT)/usr/lib/

clean:
ifneq ($(wildcard $(LIBK)),)
	rm $(LIBK)
endif
ifneq ($(wildcard $(SYSROOT)),)
	rm -r $(SYSROOT)
endif
ifneq ($(wildcard $(BUILD_DIR)),)
	rm -r $(BUILD_DIR)
endif

-include $(LINK_DEPS)
