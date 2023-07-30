#include "pci.hpp"
#include "global.hpp"
#include "simple_button.hpp"
#include "utils/hex_string.hpp"

PCI::PCI(uint64_t address) {
  mDataView = new DataView(address);
  mDeviceSelectIndex = 0;
  gDeviceSelectIndex = &mDeviceSelectIndex;
  gSelectedDeviceConfigSpace = &mSelectedDeviceConfigSpace;
  mPciDeviceBtnStr =
      hexString(gPciDevices->at(mDeviceSelectIndex).bus, 2) + ":" +
      hexString(gPciDevices->at(mDeviceSelectIndex).device, 2) + ":" +
      hexString(gPciDevices->at(mDeviceSelectIndex).function, 1);
  gPciDeviceBtnStr = &mPciDeviceBtnStr;
  gPciAddrInputStr = &mAddrInputStr;
  mPciDeviceBtn = Button(
      gPciDeviceBtnStr,
      [&] {
        gUsingDataView = mDataView;
        *gShowPciDeviceSelectModal = true;
      },
      SimpleButton());
  mPciDeviceSummaryBtn = Button(
      "Summary",
      [&] {
        getPciConfigSpace(gSelectedDeviceConfigSpace);
        *gShowPciDeviceSummaryModal = true;
      },
      SimpleButton());
  mReturnBtn = Button(
      "↵",
      [&] {
        try {
          if (mAddrInputStr.length() == 0) {
            *gMessageStr = "Please enter the address you want to move to.";
            *gShowMessageModal = true;
          } else {
            mDataView->setAddress(stoul(mAddrInputStr, nullptr, 16));
            mAddrInputStr = hexString(mDataView->getAddress(), 8);
          }
        } catch (exception e) {
          *gMessageStr = "The address you are trying to move to is not a Hex "
                         "value. Please enter a valid value.";
          *gShowMessageModal = true;
        }
      },
      SimpleButton());
  mPreviousAddrBtn = Button(
      "◀",
      [&] {
        if (mDataView->getAddress() < 0x100) {
          *gMessageStr = "It is not possible to move from the current address "
                         "to the address before 0x100.";
          *gShowMessageModal = true;
        } else {
          mDataView->toPrevious();
          mAddrInputStr = hexString(mDataView->getAddress(), 8);
        }
      },
      SimpleButton());
  mNextAddrBtn = Button(
      "▶",
      [&] {
        mDataView->toNext();
        mAddrInputStr = hexString(mDataView->getAddress(), 8);
      },
      SimpleButton());
  mRefreshBtn = Button(
      "Refresh",
      [&] {
        mDataView->refresh();
        mAddrInputStr = hexString(mDataView->getAddress(), 8);
      },
      SimpleButton());
  mAddrInputStr = hexString(address, 8);
  mAddrInput = Input(&mAddrInputStr, "Address") | size(WIDTH, LESS_THAN, 9);
  mDataViewComponent = mDataView->getComponent();
  mContainer = Container::Vertical({
                   Container::Horizontal({
                       mPciDeviceBtn,
                       mPciDeviceSummaryBtn,
                       mAddrInput,
                       mReturnBtn,
                       mPreviousAddrBtn,
                       mNextAddrBtn,
                       mRefreshBtn,
                   }),
                   mDataViewComponent,
               }) |
               CatchEvent([&](Event event) {
                 if (event == Event::PageUp) {
                   if (mDataView->getAddress() < 0x100) {
                     *gMessageStr =
                         "It is not possible to move from the current address "
                         "to the address before 0x100.";
                     *gShowMessageModal = true;
                   } else {
                     mDataView->toPrevious();
                     mAddrInputStr = hexString(mDataView->getAddress(), 8);
                   }
                   return true;
                 }
                 if (event == Event::PageDown) {
                   mDataView->toNext();
                   mAddrInputStr = hexString(mDataView->getAddress(), 8);
                   return true;
                 }
                 if (event == Event::F2) {
                   mAddrInput->TakeFocus();
                   return true;
                 }
                 if (event == Event::F5) {
                   mDataView->refresh();
                   mAddrInputStr = hexString(mDataView->getAddress(), 8);
                   return true;
                 }
                 return false;
               });
}

Component PCI::getComponent() {
  return Renderer(mContainer, [&] {
    if (mAddrInputStr.length() > 8) {
      mAddrInputStr = mAddrInputStr.substr(0, 8);
    }
    return vbox({
        hbox({
            text(" * Device : "),
            mPciDeviceBtn->Render(),
            text("  "),
            mPciDeviceSummaryBtn->Render(),
            text(" | Address : 0x"),
            text(""),
            mAddrInput->Render(),
            text(" "),
            mReturnBtn->Render(),
            text(" "),
            mPreviousAddrBtn->Render(),
            text(" "),
            mNextAddrBtn->Render(),
            text(" "),
            mRefreshBtn->Render(),
        }),
        hbox({
            mDataViewComponent->Render() | size(WIDTH, LESS_THAN, 78) |
                size(HEIGHT, EQUAL, 17) | border,
        }),
    });
  });
}
