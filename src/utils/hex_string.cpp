#include "utils/hex_string.hpp"

string hexString(uint64_t value, uint64_t digits, bool ellipsis) {
  std::stringstream stream;
  stream << setfill('0') << setw(digits) << hex << uppercase << value;
  std::string valueStr(stream.str());
  if (ellipsis == true) {
    uint64_t valueLength = valueStr.length();
    valueStr =
        valueStr.substr(0, 2) + ".." + valueStr.substr(valueLength - 4, 4);
  }
  return valueStr;
}