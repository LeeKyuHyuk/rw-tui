#include <fstream>

#include "utils/is_file_exist.hpp"

bool isFileExist(const char *fileName) {
  std::ifstream infile(fileName);
  return infile.good();
}