#include "utilities.hpp"

#include "../src/lz_string.hpp"

#include <gtest/gtest.h>

TEST(DecompressUint8Array, HelloWorld) {
  std::u16string input = pxd::lz_string::to_utf16(hello_world);

  std::vector<uint8_t> compressed = pxd::lz_string::compressUint8Array(input);
  std::u16string decompressed = pxd::lz_string::decompressUint8Array(compressed);

  EXPECT_TRUE(input == decompressed);
}

TEST(DecompressUint8Array, AllASCII) {
  std::u16string input = pxd::lz_string::to_utf16(all_ascii);

  std::vector<uint8_t> compressed = pxd::lz_string::compressUint8Array(input);
  std::u16string decompressed = pxd::lz_string::decompressUint8Array(compressed);

  EXPECT_TRUE(input == decompressed);
}

TEST(DecompressUint8Array, JSON) {
  std::u16string input = pxd::lz_string::to_utf16(temp_json);

  std::vector<uint8_t> compressed = pxd::lz_string::compressUint8Array(input);
  std::u16string decompressed = pxd::lz_string::decompressUint8Array(compressed);

  EXPECT_TRUE(input == decompressed);
}

TEST(DecompressUint8Array, JSONFloat) {
  std::u16string input = pxd::lz_string::to_utf16(temp_json_float);

  std::vector<uint8_t> compressed = pxd::lz_string::compressUint8Array(input);
  std::u16string decompressed = pxd::lz_string::decompressUint8Array(compressed);

  EXPECT_TRUE(input == decompressed);
}
