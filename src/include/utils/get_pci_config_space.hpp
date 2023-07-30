#ifndef __GET_PCI_CONFIG_SPACE_HPP__
#define __GET_PCI_CONFIG_SPACE_HPP__

#include <cstdint>

using namespace std;

typedef struct {
  uint16_t vendorId;
  uint16_t deviceId;
  uint16_t command;
  uint16_t status;
  uint8_t revisionId;
  uint8_t progInterface;
  uint8_t subClassCode;
  uint8_t baseClassCode;
  uint8_t cacheLineSize;
  uint8_t latencyTimer;
  uint8_t headerType;
  uint8_t bist;
  union {
    struct {
      uint32_t baseAddress[6];
      uint32_t cardbusCisPointer;
      uint16_t subSystemVendorId;
      uint16_t subSystemId;
      uint32_t expansionRomBaseAddr;
      uint8_t capabilitiesPointer;
      uint8_t reserved1[3];
      uint32_t reserved2;
      uint8_t interruptLine;
      uint8_t interruptPin;
      uint8_t minGrant;
      uint8_t maxLatency;
    } type0;
    struct {
      uint32_t baseAddress[2];
      uint8_t primaryBusNumber;
      uint8_t secondaryBusNumber;
      uint8_t subordinateBusNumber;
      uint8_t secondaryLatencyTimer;
      uint8_t ioBase;
      uint8_t ioLimit;
      uint16_t secondaryStatus;
      uint16_t memoryBase;
      uint16_t memoryLimit;
      uint16_t prefetchableMemoryBase;
      uint16_t prefetchableMemoryLimit;
      uint32_t prefetchableMemoryBaseUpper;
      uint32_t prefetchableMemoryLimitUpper;
      uint16_t ioBaseUpper;
      uint16_t ioLimitUpper;
      uint8_t capabilitiesPointer;
      uint8_t reserved1[3];
      uint32_t expansionRomBaseAddr;
      uint8_t interruptLine;
      uint8_t interruptPin;
      uint16_t bridgeControl;
    } type1;
  };
} PCI_CONFIG_SPACE;

void getPciConfigSpace(PCI_CONFIG_SPACE *pciConfigSpace);

#endif