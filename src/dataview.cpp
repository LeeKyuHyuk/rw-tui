#include <sstream>
#include <sys/mman.h>

#include "dataview.hpp"
#include "global.hpp"
#include "utils/hex_string.hpp"

DataView::DataView(uint64_t address) {
  mContainer = Container::Vertical({});
  mAddress = address;
  refresh();
}

uint64_t DataView::getAddress() { return mAddress; }

void DataView::toPrevious() { setAddress(mAddress - 0x100); }

void DataView::toNext() { setAddress(mAddress + 0x100); }

void DataView::setAddress(uint64_t address) {
  mAddress = address;
  refresh();
}

void DataView::refresh() {
  void *mapBase, *virtAddress;
  mContainer->DetachAllChildren();
  mapBase = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
                 *gFileDescriptor, mAddress & ~MAP_MASK);
  if (mapBase == (void *)-1)
    FATAL;
  for (uint8_t index = 0; index < TABLE_ROW_NUMBER; index += 1) {
    mTableRow[index] = Container::Horizontal({});
  }
  uint16_t rowIndex = 0;
  for (uint16_t index = 0; index < TABLE_CELL_NUMBER; index += 1) {
    uint16_t cellIndex = index;
    if (index != 0) {
      if (index % TABLE_COL_NUMBER == 0) {
        mContainer->Add(mTableRow[rowIndex]);
        rowIndex += 1;
      }
    }
    virtAddress = (uint8_t *)mapBase + (mAddress & MAP_MASK);
    uint64_t value = *((uint8_t *)virtAddress + index);
    mTableCell[cellIndex] = Button(
        hexString(value, 2),
        [&, cellIndex] {
          *gSelectAddress = (mAddress + cellIndex);
          gUsingDataView = this;
          *gShowChangeValueModal = true;
        },
        ButtonOption::Ascii());
    mTableCell[cellIndex] =
        mTableCell[cellIndex] |
        CatchEvent([&, rowIndex, cellIndex](Event event) {
          if (cellIndex > (TABLE_COL_NUMBER + 1) && event == Event::ArrowUp) {
            mTableCell[cellIndex - TABLE_COL_NUMBER]->TakeFocus();
            return true;
          }
          if (rowIndex < (TABLE_ROW_NUMBER - 1) && event == Event::ArrowDown) {
            mTableCell[cellIndex + TABLE_COL_NUMBER]->TakeFocus();
            return true;
          }
          return false;
        });
    uint64_t offsetAddress = mAddress + index;
    if (index % TABLE_COL_NUMBER == 0) {
      mTableRowLabel[rowIndex] = Renderer([&, offsetAddress,
                                           rowIndex](bool focused) {
        if (focused == true) {
          mTableCell[rowIndex * TABLE_COL_NUMBER]->TakeFocus();
        }
        if (offsetAddress > 0xFFFFFFFF) {
          return text(" 0x" + hexString(move(offsetAddress), 8, true) + " ") |
                 inverted;
        } else {
          return text(" 0x" + hexString(move(offsetAddress), 8, false) + " ") |
                 inverted;
        }
      });
      mTableRow[rowIndex]->Add(mTableRowLabel[rowIndex]);
    }
    mTableRow[rowIndex]->Add(mTableCell[cellIndex]);
  }
  mContainer->Add(mTableRow[rowIndex]);
  if (munmap(mapBase, MAP_SIZE) == -1)
    FATAL;
}

Component DataView::getComponent() {
  return Renderer(mContainer, [&] {
    return hbox({
        text(" "),
        vbox({
            mTableHeader->Render(),
            mContainer->Render() | frame,
        }),
        text(" "),
    });
  });
}
