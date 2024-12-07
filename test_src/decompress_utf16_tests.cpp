#include "utilities.hpp"

#include <gtest/gtest.h>

TEST(DecompressUTF16, HelloWorld) {
  std::string input(hello_world);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::VALID_UTF16));
}

TEST(DecompressUTF16, AllASCII) {
  std::string input(all_ascii);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::VALID_UTF16));
}

TEST(DecompressUTF16, JSON) {
  std::string input(temp_json);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::VALID_UTF16));
}

TEST(DecompressUTF16, JSONFloat) {
  std::string input(temp_json_float);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::VALID_UTF16));
}
