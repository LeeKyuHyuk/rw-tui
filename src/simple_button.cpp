#include "simple_button.hpp"

ButtonOption SimpleButton() {
  ButtonOption option;
  option.transform = [](const EntryState &s) {
    return s.focused ? text(" " + s.label + " ") | inverted
                     : text("[" + s.label + "]");
  };
  return option;
}