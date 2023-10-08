#include <drivers/pci.h>

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <kernel/io.h>

uint16_t pci_config_read_word(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
	uint32_t address;
	uint32_t lbus  = (uint32_t)bus;
	uint32_t lslot = (uint32_t)slot;
	uint32_t lfunc = (uint32_t)function;
	uint16_t tmp = 0;

	// Create configuration address as per Figure 1
	address = (uint32_t)((lbus << 16) | (lslot << 11) |
			(lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));

	// Write out the address
	outl(0xCF8, address);
	// Read in the data
	// (offset & 2) * 8) = 0 will choose the first word of the 32-bit register
	tmp = (uint16_t)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
	return tmp;
}

bool pci_function_exists(uint8_t bus, uint8_t slot, uint8_t function) {
    return !(pci_config_read_word(bus, slot, function, 0) == 0xFFFF);
}

void pci_check_function(uint8_t bus, uint8_t slot, uint8_t function) {
	uint16_t vendor = pci_config_read_word(bus, slot, function, 0);
	uint16_t device = pci_config_read_word(bus, slot, function, 2);
	uint16_t class  = pci_config_read_word(bus, slot, function, 10);
    uint16_t progif = pci_config_read_word(bus, slot, function, 8);
	printf("%d:%d.%d:\n    [%x%x:%x%x] 0x%x.%x.%x\n", bus, slot, function, vendor >> 8, vendor, device >> 8, device, class >> 8, class, progif >> 8);
}

void pci_check_all_buses() {
	for (uint16_t bus = 0; bus < 256; bus++) {
		for (uint8_t slot = 0; slot < 32; slot++) {
			uint8_t function = 0;
            if (!pci_function_exists(bus, slot, function)) continue;
			
			pci_check_function(bus, slot, function);

			uint16_t header = pci_config_read_word(bus, slot, function, 14);
			if (header & 0x80) { // Multifunction, check other functions
				for (function = 1; function < 8; function++) {
					if (pci_function_exists(bus, slot, function)) {
						pci_check_function(bus, slot, function);
					}
				}
			}
		}
	}
}

struct pci_function pci_find_function(uint8_t class, uint8_t subclass) {
	for (uint16_t bus = 0; bus < 256; bus++) {
		for (uint8_t slot = 0; slot < 32; slot++) {
            uint8_t function = 0;
            if (!pci_function_exists(bus, slot, function)) continue;

            uint16_t c = pci_config_read_word(bus, slot, function, 10);
            if (c >> 8 == class && (uint8_t)c == subclass)
			    return (struct pci_function){.bus = bus, .slot = slot, .function = function};

			uint16_t header = pci_config_read_word(bus, slot, 0, 14);
            if (header & 0x80) { // Multifunction PCI device
    		    for (function = 1; function < 8; function++) {
			        if (!pci_function_exists(bus, slot, function)) continue;

        	    	uint16_t c = pci_config_read_word(bus, slot, function, 10);
		        	if (c >> 8 == class && (uint8_t)c == subclass)
			            return (struct pci_function){.bus = bus, .slot = slot, .function = function};
                }
            }
		}
	}

	printf("Couldn't find PCI device with class %d and subclass %d", class, subclass);
	asm volatile("cli\n\thlt");
}

void pci_find_BARs(uint8_t bus, uint8_t slot, uint8_t function) {
    uint8_t header = pci_config_read_word(bus, slot, function, 14) & 3;
    if (header == 0) {
	    uint32_t bars[6] = {0};
	    for (int i = 0; i < 6; i++) {
	    	bars[i] = pci_config_read_word(bus, slot, function, 16 + i * 4) + (pci_config_read_word(bus, slot, function, 18 + i * 4) << 16);
	    	printf("0x%x%x%x%x\n", (uint8_t)(bars[i] >> 24), (uint8_t)(bars[i] >> 16), (uint8_t)(bars[i] >> 8), (uint8_t)bars[i]);
	    }
    }
}
