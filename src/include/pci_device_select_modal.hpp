#ifndef __PCI_DEVICE_SELECT_MODAL_HPP__
#define __PCI_DEVICE_SELECT_MODAL_HPP__

#include <string>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#include "acpi/mcfg.hpp"

using namespace std;
using namespace ftxui;

class PciDeviceSelectModal {
private:
  MCFG *mcfg;
  vector<string> mDevices;
  int mDeviceSelectIndex;
  Component mSelectDropdown;
  Component mSubmitBtn;
  Component mCloseBtn;
  Component mContainer;
  void closeModal();
  void submit();

public:
  PciDeviceSelectModal();
  Component getComponent();
};

#endif