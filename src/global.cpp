#include "global.hpp"

int *gFileDescriptor;
uint64_t *gBaseAddress;
DataView *gUsingDataView;
bool *gShowChangeValueModal;
uint64_t *gSelectAddress;
bool *gShowPciDeviceSelectModal;
vector<PCI_DEVICE> *gPciDevices;
string *gPciDeviceBtnStr;
string *gPciAddrInputStr;
bool *gShowPciDeviceSummaryModal;
int *gDeviceSelectIndex;
PCI_CONFIG_SPACE *gSelectedDeviceConfigSpace;
bool *gShowMessageModal;
string *gMessageStr;