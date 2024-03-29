#include <stdint.h>

void outb(uint16_t port, uint8_t data) {
    asm volatile("outb %0, %1" : : "a"(data), "d"(port));
}

void outw(uint16_t port, uint16_t data) {
    asm volatile("outw %0, %1" : : "a"(data), "d"(port));
}

void outl(uint16_t port, uint32_t data) {
    asm volatile("outl %0, %1" : : "a"(data), "d"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}

uint16_t inw(uint16_t port) {
    uint16_t ret;
    asm volatile("inw %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}

uint16_t inl(uint16_t port) {
    uint32_t ret;
    asm volatile("inl %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}

void io_wait(void) {
    outb(0x80, 0);
}
