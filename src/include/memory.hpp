#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include <string>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#include "dataview.hpp"

using namespace std;
using namespace ftxui;

class Memory {
private:
  DataView *mDataView;
  Component mReturnBtn;
  Component mPreviousAddrBtn;
  Component mNextAddrBtn;
  Component mRefreshBtn;
  Component mAddrInput;
  string mAddrInputStr;
  Component mDataViewComponent;
  Component mContainer;

public:
  Memory(uint64_t address);
  Component getComponent();
};

#endif