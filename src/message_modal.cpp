#include "message_modal.hpp"
#include "global.hpp"

MessageModal::MessageModal() {
  mCloseBtn = Button(
      " Close ", [&] { closeModal(); }, ButtonOption::Border());
  mContainer = Container::Vertical({
      mCloseBtn,
  });
}

void MessageModal::closeModal() { *gShowMessageModal = false; }

Component MessageModal::getComponent() {
  return Renderer(mContainer, [&] {
    return vbox({
               paragraph(*gMessageStr),
               separatorLight(),
               hbox({
                   mCloseBtn->Render(),
               }) | center,
           }) |
           size(WIDTH, EQUAL, 45) | border;
  });
}
