#include <sys/mman.h>

#include "global.hpp"
#include "pci_device_summary_modal.hpp"
#include "utils/hex_string.hpp"

PciDeviceSummaryModal::PciDeviceSummaryModal() {
  mCloseBtn = Button(
      " Close ", [&] { closeModal(); }, ButtonOption::Border());
  mContainer = Container::Vertical({
      mCloseBtn,
  });
}

void PciDeviceSummaryModal::closeModal() {
  *gShowPciDeviceSummaryModal = false;
  mCloseBtn->TakeFocus();
}

Component PciDeviceSummaryModal::getComponent() {
  return Renderer(mContainer, [&] {
    return vbox({
               hbox({
                   vbox({
                       text(" Vendor ID : 0x" +
                            hexString(gSelectedDeviceConfigSpace->vendorId, 4)),
                       text(" Device ID : 0x" +
                            hexString(gSelectedDeviceConfigSpace->deviceId, 4)),
                       text(" Command : 0x" +
                            hexString(gSelectedDeviceConfigSpace->command, 4)),
                       text(" Status : 0x" +
                            hexString(gSelectedDeviceConfigSpace->status, 4)),
                       text(" Revision ID : 0x" +
                            hexString(gSelectedDeviceConfigSpace->revisionId,
                                      2)),
                       text(" Programming Interface : 0x" +
                            hexString(gSelectedDeviceConfigSpace->progInterface,
                                      2)),
                       text(" Sub-Class Code : 0x" +
                            hexString(gSelectedDeviceConfigSpace->subClassCode,
                                      2)),
                       text(" Base Class Code : 0x" +
                            hexString(gSelectedDeviceConfigSpace->baseClassCode,
                                      2)),
                       text(" Cache Line Size : 0x" +
                            hexString(gSelectedDeviceConfigSpace->cacheLineSize,
                                      2)),
                       text(" Latency Timer : 0x" +
                            hexString(gSelectedDeviceConfigSpace->latencyTimer,
                                      2)),
                       text(" Header Type : 0x" +
                            hexString(gSelectedDeviceConfigSpace->headerType,
                                      2)),
                       text(" BIST : 0x" +
                            hexString(gSelectedDeviceConfigSpace->bist, 2)),
                   }),
                   text(" "),
                   separatorLight(),
                   gSelectedDeviceConfigSpace->headerType == 0x00
                       ? vbox({
                             text(" Base Address[0] : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .baseAddress[0],
                                            8)),
                             text(" Base Address[1] : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .baseAddress[1],
                                            8)),
                             text(" Base Address[2] : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .baseAddress[2],
                                            8)),
                             text(" Base Address[3] : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .baseAddress[3],
                                            8)),
                             text(" Base Address[4] : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .baseAddress[4],
                                            8)),
                             text(" Base Address[5] : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .baseAddress[5],
                                            8)),
                             text(" Cardbus CIS Pointer : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .cardbusCisPointer,
                                            8)),
                             text(" Subsystem Vendor ID : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .subSystemVendorId,
                                            4)),
                             text(" Subsystem ID : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .subSystemId,
                                            4)),
                             text(" Expansion ROM Base Address : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .expansionRomBaseAddr,
                                            8)),
                             text(" Capabilities Pointer : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .capabilitiesPointer,
                                            2)),
                             text(" Interrupt Line : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .interruptLine,
                                            2)),
                             text(" Interrupt Pin : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .interruptPin,
                                            2)),
                             text(" Min Grant : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .minGrant,
                                            2)),
                             text(" Max Latency : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .maxLatency,
                                            2)),
                         })
                       : vbox({
                             text(" Base Address[0] : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .baseAddress[0],
                                            8)),
                             text(" Base Address[1] : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .baseAddress[1],
                                            8)),
                             text(" Primary Bus Number : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .primaryBusNumber,
                                            2)),
                             text(" Secondary Bus Number : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .secondaryBusNumber,
                                            2)),
                             text(" Subordinate Bus Number : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .subordinateBusNumber,
                                            2)),
                             text(" Secondary Latency Timer : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .secondaryLatencyTimer,
                                            2)),
                             text(" I/O Base : 0x" +
                                  hexString(
                                      gSelectedDeviceConfigSpace->type1.ioBase,
                                      2) +
                                  " , I/O Limit : 0x" +
                                  hexString(
                                      gSelectedDeviceConfigSpace->type1.ioLimit,
                                      2)),
                             text(" Secondary Status : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .secondaryStatus,
                                            4)),
                             text(" Memory Base : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .memoryBase,
                                            4) +
                                  " , Memory Limit : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .memoryLimit,
                                            4)),
                             text(" Prefetchable Memory Base : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .prefetchableMemoryBase,
                                            4)),
                             text(" Prefetchable Memory Limit : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .prefetchableMemoryLimit,
                                            4)),
                             text(" Prefetchable Memory Base Upper : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .prefetchableMemoryBaseUpper,
                                            8)),
                             text(" Prefetchable Memory Limit Upper : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .prefetchableMemoryLimitUpper,
                                            8)),
                             text(" I/O Base Upper : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .ioBaseUpper,
                                            4)),
                             text(" I/O Limit Upper : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .ioLimitUpper,
                                            4)),
                             text(" Capabilities Pointer : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .capabilitiesPointer,
                                            2)),
                             text(" Expansion ROM Base Address : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type1
                                                .expansionRomBaseAddr,
                                            8)),
                             text(" Interrupt Line : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .interruptLine,
                                            2) +
                                  " , Interrupt Pin : 0x" +
                                  hexString(gSelectedDeviceConfigSpace->type0
                                                .interruptPin,
                                            2)),
                         }),
               }),
               separator(),
               hbox({
                   mCloseBtn->Render(),
               }) | center,
           }) |
           size(WIDTH, GREATER_THAN, 40) | border;
  });
}
