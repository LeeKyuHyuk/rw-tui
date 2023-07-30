#ifndef __PCI_DEVICE_SUMMARY_MODAL_HPP__
#define __PCI_DEVICE_SUMMARY_MODAL_HPP__

#include <string>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace std;
using namespace ftxui;

class PciDeviceSummaryModal {
private:
  Component mCloseBtn;
  Component mContainer;
  void closeModal();

public:
  PciDeviceSummaryModal();
  Component getComponent();
};

#endif