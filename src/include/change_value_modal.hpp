#ifndef __CHANGE_VALUE_MODAL_HPP__
#define __CHANGE_VALUE_MODAL_HPP__

#include <string>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace std;
using namespace ftxui;

class ChangeValueModal {
private:
  Component mValueInput;
  string mValueInputStr;
  Component mSubmitBtn;
  Component mCloseBtn;
  Component mContainer;
  void closeModal();
  void changeValue();

public:
  ChangeValueModal();
  Component getComponent();
};

#endif