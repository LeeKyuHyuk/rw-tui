#ifndef __GLOBAL_HPP__
#define __GLOBAL_HPP__

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>

#include "dataview.hpp"
#include "utils/get_pci_config_space.hpp"
#include "utils/get_pci_devices.hpp"

#define FATAL                                                                  \
  do {                                                                         \
    fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", __LINE__,         \
            __FILE__, errno, strerror(errno));                                 \
    exit(1);                                                                   \
  } while (0)

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

using namespace std;

extern int *gFileDescriptor;
extern uint64_t *gBaseAddress;
extern DataView *gUsingDataView;
extern bool *gShowChangeValueModal;
extern uint64_t *gSelectAddress;
extern bool *gShowPciDeviceSelectModal;
extern vector<PCI_DEVICE> *gPciDevices;
extern string *gPciDeviceBtnStr;
extern string *gPciAddrInputStr;
extern bool *gShowPciDeviceSummaryModal;
extern int *gDeviceSelectIndex;
extern PCI_CONFIG_SPACE *gSelectedDeviceConfigSpace;
extern bool *gShowMessageModal;
extern string *gMessageStr;

#endif