#ifndef __HEX_STRING_HPP__
#define __HEX_STRING_HPP__

#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

string hexString(uint64_t value, uint64_t digits, bool ellipsis = false);

#endif