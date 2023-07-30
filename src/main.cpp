#include <cstdint>
#include <fcntl.h>
#include <memory>
#include <string>
#include <unistd.h>
#include <vector>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#include "acpi/mcfg.hpp"
#include "change_value_modal.hpp"
#include "dataview.hpp"
#include "global.hpp"
#include "memory.hpp"
#include "message_modal.hpp"
#include "pci.hpp"
#include "pci_device_select_modal.hpp"
#include "pci_device_summary_modal.hpp"
#include "utils/get_pci_devices.hpp"
#include "utils/hex_string.hpp"
#include "utils/is_file_exist.hpp"

#define DEV_MEM "/dev/mem"
#define DEV_FMEM "/dev/fmem"

using namespace std;
using namespace ftxui;

const string RW_TUI_VERSION = "v1.0.0";

int main(int argc, char *argv[]) {
  int c = 0;
  while ((c = getopt(argc, argv, "v")) != -1)
    switch (c) {
    case 'v':
      cout << endl;
      cout << "rw-tui " << RW_TUI_VERSION << endl;
      cout << "Copyright (C) 2023, KyuHyuk Lee <lee@kyuhyuk.kr>" << endl;
      cout << "https://github.com/LeeKyuHyuk/rw-tui" << endl;
      cout << endl;
      return EXIT_SUCCESS;

    default:
      return EXIT_FAILURE;
    }

  if (getuid() != 0) {
    cerr << "[ERROR] rw-tui must be run with root privileges." << endl;
    return EXIT_FAILURE;
  }

  bool showChangeValueModal = false;
  uint64_t selectAddress = 0;
  gShowChangeValueModal = &showChangeValueModal;
  gSelectAddress = &selectAddress;

  bool showPciDeviceSelectModal = false;
  bool showPciDeviceSummaryModal = false;
  gShowPciDeviceSelectModal = &showPciDeviceSelectModal;
  gShowPciDeviceSummaryModal = &showPciDeviceSummaryModal;
  vector<PCI_DEVICE> mPciDevices;
  gPciDevices = &mPciDevices;
  getPciDevices(gPciDevices);

  bool showMessageModal = false;
  string messageStr = "";
  gShowMessageModal = &showMessageModal;
  gMessageStr = &messageStr;

  if (isFileExist(DEV_FMEM) == false) {
    if (isFileExist(DEV_MEM) == false) {
      cerr << "[ERROR] Neither /dev/mem nor /dev/fmem exist.\nGet the source "
              "code of "
              "'fmem' Kernel Module from https://github.com/LeeKyuHyuk/fmem, "
              "build it, and use it."
           << endl;
      return EXIT_FAILURE;
    } else {
      cerr << "[ERROR] 'fmem' module was not inserted into the kernel.\nWhen "
              "CONFIG_STRICT_DEVMEM and CONFIG_IO_STRICT_DEVMEM of Kernel "
              "Config "
              "are set to Yes, rw-tui may not work properly if /dev/mem is "
              "used.\nGet the source code of fmem Kernel Module from "
              "https://github.com/LeeKyuHyuk/fmem, build it, and use it."
           << endl;
      return EXIT_FAILURE;
    }
  }

  int fileDescriptor;
  if ((fileDescriptor = open(DEV_FMEM, O_RDWR | O_SYNC)) == -1)
    FATAL;
  gFileDescriptor = &fileDescriptor;

  uint64_t baseAddress = (new MCFG())->getMcfgTable().allocation->baseAddress;
  gBaseAddress = &baseAddress;

  int tabSelected = 0;
  vector<string> tabValues{
      " Memory ",
      " PCI ",
  };
  auto tabToggle =
      Menu(&tabValues, &tabSelected, MenuOption::Horizontal()) | border;

  Component tabContainer = Container::Tab(
      {
          (new Memory(0x00000000))->getComponent(),
          (new PCI(*gBaseAddress))->getComponent(),
      },
      &tabSelected);

  Component container = Container::Vertical({
      tabToggle,
      tabContainer,
  });

  Component renderer = Renderer(container, [&] {
    return vbox({
        text("rw-tui " + RW_TUI_VERSION) | bold | hcenter,
        tabToggle->Render(),
        tabContainer->Render() | frame | flex,
    });
  });

  renderer |=
      Modal((new ChangeValueModal())->getComponent(), gShowChangeValueModal);
  renderer |= Modal((new PciDeviceSelectModal())->getComponent(),
                    gShowPciDeviceSelectModal);
  renderer |= Modal((new PciDeviceSummaryModal())->getComponent(),
                    gShowPciDeviceSummaryModal);
  renderer |= Modal((new MessageModal())->getComponent(), gShowMessageModal);

  ScreenInteractive screen = ScreenInteractive::Fullscreen();
  screen.Loop(renderer | size(WIDTH, EQUAL, 80) | size(HEIGHT, EQUAL, 24) |
              center);
  close(fileDescriptor);
  return EXIT_SUCCESS;
}