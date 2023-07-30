#include <sys/mman.h>

#include "change_value_modal.hpp"
#include "global.hpp"
#include "utils/hex_string.hpp"

ChangeValueModal::ChangeValueModal() {
  mValueInputStr = "";
  mValueInput = Input(&mValueInputStr, "00") | size(WIDTH, EQUAL, 3);
  mSubmitBtn = Button(
      " Submit ",
      [&] {
        changeValue();
        closeModal();
      },
      ButtonOption::Border());
  mCloseBtn = Button(
      " Close ", [&] { closeModal(); }, ButtonOption::Border());
  mContainer = Container::Vertical({
      mValueInput,
      Container::Horizontal({
          mSubmitBtn,
          mCloseBtn,
      }),
  });
}

void ChangeValueModal::closeModal() {
  *gShowChangeValueModal = false;
  mValueInputStr = "";
  mValueInput->TakeFocus();
  gUsingDataView->refresh();
}

void ChangeValueModal::changeValue() {
  try {
    if (mValueInputStr.length() == 0) {
      *gMessageStr = "Enter the value you want to write.";
      *gShowMessageModal = true;
    } else {
      void *mapBase, *virtAddress;
      mapBase = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
                     *gFileDescriptor, *gSelectAddress & ~MAP_MASK);
      if (mapBase == (void *)-1)
        FATAL;
      virtAddress = (uint8_t *)mapBase + (*gSelectAddress & MAP_MASK);
      *((unsigned char *)virtAddress) = stoul(mValueInputStr, nullptr, 16);
      if (munmap(mapBase, MAP_SIZE) == -1)
        FATAL;
    }
  } catch (exception e) {
    *gMessageStr = "The value to be written is not a Hex value. Please enter a "
                   "valid value.";
    *gShowMessageModal = true;
  }
}

Component ChangeValueModal::getComponent() {
  return Renderer(mContainer, [&] {
    if (mValueInputStr.length() > 2) {
      mValueInputStr = mValueInputStr.substr(0, 2);
    }
    return vbox({
               text(" Change the value of 0x" + hexString(*gSelectAddress, 8)),
               separator(),
               hbox({
                   text(" Value : 0x"),
                   mValueInput->Render(),
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
