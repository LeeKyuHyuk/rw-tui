#include "acpi/mcfg.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

MCFG::MCFG() {
  ifstream ifs(MCFG_PATH, ios::binary);
  ifs.read(reinterpret_cast<char *>(&mcfgTable), sizeof(MCFG_TABLE));
  ifs.close();
}

MCFG_TABLE MCFG::getMcfgTable() { return mcfgTable; }