#include <iostream>

#include "src/lz_string.hpp"

auto main() -> int {
  std::string input = "hello there";

  std::u16string str_16(input.begin(), input.end());

  std::cout << pxd::lz_string::to_utf8(str_16) << "\n";

  std::string encoded =
      pxd::lz_string::to_utf8(pxd::lz_string::compress(str_16));

  std::cout << encoded << "\n";

  return 0;
}