#include <kernel/idt.h>

#include <kernel/isr.h>

idtr IDTR;
interrupt IDT[256];

void idt_load() {
    IDTR.limit  = 256*(sizeof(interrupt)-1);
    IDTR.base   = IDT;

    asm volatile("LIDT (%0) ": :"g" (IDTR));
}

void idt_add_interrupt(int number, void (*handler)()) {
    uint16_t selector = 0x08;
    uint32_t offset = (uint32_t)handler;

    asm volatile("movw %%cs,%0" :"=g"(selector));

    IDT[number].offset_low   = (offset & 0xFFFF);
    IDT[number].selector     = selector;
    IDT[number].settings     = INT_OPTS_R0;
    IDT[number].offset_high  = (offset >> 16);
    IDT[number].zero         = 0;
}

void idt_init() {
    idt_add_interrupt(0, intw0);
    idt_add_interrupt(1, intw1);
    idt_add_interrupt(2, intw2);
    idt_add_interrupt(3, intw3);
    idt_add_interrupt(4, intw4);
    idt_add_interrupt(5, intw5);
    idt_add_interrupt(6, intw6);
    idt_add_interrupt(7, intw7);
    idt_add_interrupt(8, intw8);
    idt_add_interrupt(9, intw9);
    idt_add_interrupt(10, intw10);
    idt_add_interrupt(11, intw11);
    idt_add_interrupt(12, intw12);
    idt_add_interrupt(13, intw13);
    idt_add_interrupt(14, intw14);
    idt_add_interrupt(15, intw15);
    idt_add_interrupt(16, intw16);
    idt_add_interrupt(17, intw17);
    idt_add_interrupt(18, intw18);
    idt_add_interrupt(19, intw19);

    idt_add_interrupt(32, intw32);
    idt_add_interrupt(33, intw33);
    idt_add_interrupt(34, intw34);
    idt_add_interrupt(35, intw35);
    idt_add_interrupt(36, intw36);
    idt_add_interrupt(37, intw37);
    idt_add_interrupt(38, intw38);
    idt_add_interrupt(39, intw39);
    idt_add_interrupt(40, intw40);
    idt_add_interrupt(41, intw41);
    idt_add_interrupt(42, intw42);
    idt_add_interrupt(43, intw43);
    idt_add_interrupt(44, intw44);
    idt_add_interrupt(45, intw45);
    idt_add_interrupt(46, intw46);
    idt_add_interrupt(47, intw47);

    idt_load();
}
