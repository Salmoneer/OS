#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/io.h>
#include <kernel/tty.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <drivers/pci.h>

void kernel_main() {
    terminal_initialize();

    asm volatile("cli");

    pic_remap(32, 40);

    idt_init();

    /* Only enable keyboard interrupts */
    outb(0x21, 0xfd);
    outb(0xa1, 0xff);

    asm volatile("sti");

    printf("Probably sort of an OS sometime this century\n\n");

    pci_check_all_buses();
    struct pci_function ide = pci_find_function(1, 1);
    pci_find_BARs(ide.bus, ide.slot, ide.function);
}
