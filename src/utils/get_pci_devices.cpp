#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "utils/get_pci_devices.hpp"
#include "utils/hex_string.hpp"

void getPciDevices(vector<PCI_DEVICE> *pciDevices) {
  pciDevices->clear();
  const uint16_t domain = 0;
  for (uint16_t bus = 0; bus < 256; ++bus) {
    for (uint8_t device = 0; device < 32; ++device) {
      for (uint8_t function = 0; function < 8; ++function) {
        string path = "/sys/bus/pci/devices/0000:" + hexString(bus, 2) + ":" +
                      hexString(device, 2) + "." + hexString(function, 1);

        ifstream file;
        file.open((path + "/vendor").c_str());
        if (!file) {
          continue;
        }

        string vendorId;
        file >> vendorId;
        file.close();

        file.open((path + "/device").c_str());
        if (!file) {
          continue;
        }

        string deviceId;
        file >> deviceId;
        file.close();

        PCI_DEVICE item = {
            .bus = bus,
            .device = device,
            .function = function,
            .vendorId = (uint16_t)stoul(vendorId, nullptr, 16),
            .deviceId = (uint16_t)stoul(deviceId, nullptr, 16),
        };

        pciDevices->push_back(item);
      }
    }
  }
}