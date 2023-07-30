#ifndef __GET_PCI_DEVICES_HPP__
#define __GET_PCI_DEVICES_HPP__

#include <cstdint>
#include <vector>

using namespace std;

typedef struct {
  uint16_t bus;
  uint8_t device;
  uint8_t function;
  uint16_t vendorId;
  uint16_t deviceId;
} PCI_DEVICE;

void getPciDevices(vector<PCI_DEVICE> *pciDevices);

#endif