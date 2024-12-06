#include <iostream>

#include "src/lz_string.hpp"

auto main() -> int {
  std::string input = "hello there !!!";

  std::u16string compressed =
      pxd::lz_string::compressEncodedURI(pxd::lz_string::to_utf16(input));

  std::u16string decompressed =
      pxd::lz_string::decompressEncodedURI(compressed);

  return 0;
}