#include "pci_device_select_modal.hpp"
#include "global.hpp"
#include "utils/hex_string.hpp"

PciDeviceSelectModal::PciDeviceSelectModal() {
  mcfg = new MCFG();
  mDevices.clear();
  for (vector<PCI_DEVICE>::iterator iter = gPciDevices->begin();
       iter != gPciDevices->end(); iter++) {
    mDevices.push_back(
        hexString(iter->bus, 2) + ":" + hexString(iter->device, 2) + ":" +
        hexString(iter->function, 1) + " - 0x" + hexString(iter->vendorId, 4) +
        ":0x" + hexString(iter->deviceId, 4));
  }
  mDeviceSelectIndex = 0;
  mSelectDropdown = Dropdown(&mDevices, &mDeviceSelectIndex) |
                    size(WIDTH, EQUAL, 40) | size(HEIGHT, LESS_THAN, 8) |
                    CatchEvent([&](Event event) {
                      if (event == Event::Tab) {
                        mSubmitBtn->TakeFocus();
                        return true;
                      }
                      return false;
                    });
  mSubmitBtn = Button(
      " Submit ",
      [&] {
        submit();
        closeModal();
      },
      ButtonOption::Border());
  mCloseBtn = Button(
      " Close ", [&] { closeModal(); }, ButtonOption::Border());
  mContainer = Container::Vertical({
      mSelectDropdown,
      Container::Horizontal({
          mSubmitBtn,
          mCloseBtn,
      }),
  });
}

void PciDeviceSelectModal::closeModal() {
  *gShowPciDeviceSelectModal = false;
  mSelectDropdown->TakeFocus();
  gUsingDataView->refresh();
}

void PciDeviceSelectModal::submit() {
  uint64_t address = *gBaseAddress +
                     (gPciDevices->at(mDeviceSelectIndex).bus << 20) +
                     (gPciDevices->at(mDeviceSelectIndex).device << 15) +
                     (gPciDevices->at(mDeviceSelectIndex).function << 12);
  *gPciDeviceBtnStr =
      hexString(gPciDevices->at(mDeviceSelectIndex).bus, 2) + ":" +
      hexString(gPciDevices->at(mDeviceSelectIndex).device, 2) + ":" +
      hexString(gPciDevices->at(mDeviceSelectIndex).function, 1);
  *gPciAddrInputStr = hexString(address, 8);
  gUsingDataView->setAddress(address);
  *gDeviceSelectIndex = mDeviceSelectIndex;
}

Component PciDeviceSelectModal::getComponent() {
  return Renderer(mContainer, [&] {
    return vbox({
               text(" Select PCI Device"),
               separator(),
               text(" PCI Device(Bus, Device, Function) : "),
               hbox({
                   mSelectDropdown->Render(),
               }),
               separator(),
               hbox({
                   mSubmitBtn->Render(),
                   text("  "),
                   mCloseBtn->Render(),
               }) | center,
           }) |
           size(WIDTH, GREATER_THAN, 40) | border;
  });
}
