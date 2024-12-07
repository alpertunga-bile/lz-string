#include "utilities.hpp"

#include <gtest/gtest.h>

TEST(Decompress, HelloWorld) {
  std::string input(hello_world);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::INVALID_UTF16));
}

TEST(Decompress, AllASCII) {
  std::string input(all_ascii);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::INVALID_UTF16));
}

TEST(Decompress, JSON) {
  std::string input(temp_json);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::INVALID_UTF16));
}

TEST(Decompress, JSONFloat) {
  std::string input(temp_json_float);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::INVALID_UTF16));
}
