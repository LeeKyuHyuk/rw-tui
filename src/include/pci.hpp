#ifndef __PCI_HPP__
#define __PCI_HPP__

#include <string>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#include "dataview.hpp"
#include "utils/get_pci_config_space.hpp"

using namespace std;
using namespace ftxui;

class PCI {
private:
  DataView *mDataView;
  int mDeviceSelectIndex;
  PCI_CONFIG_SPACE mSelectedDeviceConfigSpace;
  Component mPciDeviceBtn;
  string mPciDeviceBtnStr;
  Component mPciDeviceSummaryBtn;
  Component mReturnBtn;
  Component mPreviousAddrBtn;
  Component mNextAddrBtn;
  Component mRefreshBtn;
  Component mAddrInput;
  string mAddrInputStr;
  Component mDataViewComponent;
  Component mContainer;

public:
  PCI(uint64_t address);
  Component getComponent();
};

#endif