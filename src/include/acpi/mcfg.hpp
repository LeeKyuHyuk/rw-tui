#ifndef __ACPI_MCFG_HPP__
#define __ACPI_MCFG_HPP__

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#define MCFG_PATH "/sys/firmware/acpi/tables/MCFG"
#define PACKED __attribute__((packed))

using namespace std;
using namespace ftxui;

typedef struct {
  uint8_t signature[4];
  uint32_t length;
  uint8_t revision;
  uint8_t checksum;
  uint8_t oemId[6];
  uint8_t oemTableId[8];
  uint32_t oemRevision;
  uint8_t creatorId[4];
  uint32_t creatorRevision;
} PACKED TABLE_HEADER;

typedef struct {
  uint64_t baseAddress;
  uint16_t pciSegmentGroupNumber;
  uint8_t startBusNumber;
  uint8_t endBusNumber;
  uint32_t reserved;
} PACKED MCFG_ALLOCATION;

typedef struct {
  TABLE_HEADER header;
  uint64_t reserved;
  MCFG_ALLOCATION allocation[256];
} PACKED MCFG_TABLE;

class MCFG {
private:
  MCFG_TABLE mcfgTable;

public:
  MCFG();
  MCFG_TABLE getMcfgTable();
  Component getComponent();
};

#endif