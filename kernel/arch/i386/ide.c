#include <drivers/ide.h>

#include <drivers/pci.h>

struct pci_function ide_find_pci_controller() {
    return pci_find_function(1, 1);
}
