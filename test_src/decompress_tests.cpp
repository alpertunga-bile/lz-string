#include "utilities.hpp"

#include "../src/lz_string.hpp"

#include <gtest/gtest.h>

bool compare(std::string_view input) {
  std::u16string compressed = get_compressed(input, LZStringOptions::INVALID_UTF16);
  std::u16string decompressed = get_decompressed(compressed, LZStringOptions::INVALID_UTF16);

  return pxd::lz_string::to_utf16(input) == decompressed;
}

TEST(Decompress, HelloWorld) {
  std::string input(hello_world);

  EXPECT_TRUE(compare(input));
}

TEST(Decompress, AllASCII) {
  std::string input(all_ascii);

  EXPECT_TRUE(compare(input));
}

TEST(Decompress, JSON) {
  std::string input(temp_json);

  EXPECT_TRUE(compare(input));
}

TEST(Decompress, JSONFloat) {
  std::string input(temp_json_float);

  EXPECT_TRUE(compare(input));
}
