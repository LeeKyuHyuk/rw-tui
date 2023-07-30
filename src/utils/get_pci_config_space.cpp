#include <cstring>
#include <sys/mman.h>

#include "global.hpp"
#include "utils/get_pci_config_space.hpp"

void getPciConfigSpace(PCI_CONFIG_SPACE *pciConfigSpace) {
  uint64_t address = *gBaseAddress +
                     (gPciDevices->at(*gDeviceSelectIndex).bus << 20) +
                     (gPciDevices->at(*gDeviceSelectIndex).device << 15) +
                     (gPciDevices->at(*gDeviceSelectIndex).function << 12);
  void *mapBase, *virtAddress;
  mapBase = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
                 *gFileDescriptor, address & ~MAP_MASK);
  if (mapBase == (void *)-1)
    FATAL;
  virtAddress = (uint8_t *)mapBase + (address & MAP_MASK);
  memcpy(pciConfigSpace, virtAddress, sizeof(PCI_CONFIG_SPACE));
  if (munmap(mapBase, MAP_SIZE) == -1)
    FATAL;
}