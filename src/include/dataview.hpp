#ifndef __DATAVIEW_HPP__
#define __DATAVIEW_HPP__

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#define TABLE_COL_NUMBER 16
#define TABLE_ROW_NUMBER 16
#define TABLE_CELL_NUMBER (TABLE_COL_NUMBER * TABLE_ROW_NUMBER)

using namespace std;
using namespace ftxui;

class DataView {
private:
  Component mTableHeader = Renderer([] {
    return hbox({
        text("            "),
        text(" 00 ") | inverted,
        text(" 01 ") | inverted,
        text(" 02 ") | inverted,
        text(" 03 ") | inverted,
        text(" 04 ") | inverted,
        text(" 05 ") | inverted,
        text(" 06 ") | inverted,
        text(" 07 ") | inverted,
        text(" 08 ") | inverted,
        text(" 09 ") | inverted,
        text(" 0A ") | inverted,
        text(" 0B ") | inverted,
        text(" 0C ") | inverted,
        text(" 0D ") | inverted,
        text(" 0E ") | inverted,
        text(" 0F ") | inverted,
    });
  });
  Component mTableCell[TABLE_CELL_NUMBER];
  Component mTableRow[TABLE_ROW_NUMBER];
  Component mTableRowLabel[TABLE_ROW_NUMBER];
  Component mContainer;
  off_t mAddress;

public:
  DataView(uint64_t address);
  uint64_t getAddress();
  void setAddress(uint64_t address);
  void toPrevious();
  void toNext();
  void refresh();
  Component getComponent();
};

#endif