#ifndef PCI_H
#define PCI_H

#include <stdint.h>
#include <stdbool.h>

struct pci_function {
    uint8_t bus;
    uint8_t slot;
    uint8_t function;
};

uint16_t pci_config_read_word(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);

bool pci_function_exists(uint8_t bus, uint8_t slot, uint8_t function);

void pci_check_function(uint8_t bus, uint8_t slot, uint8_t function);

void pci_check_all_buses(void);

struct pci_function pci_find_function(uint8_t class, uint8_t subclass);

void pci_find_BARs(uint8_t bus, uint8_t slot, uint8_t function);

#endif
