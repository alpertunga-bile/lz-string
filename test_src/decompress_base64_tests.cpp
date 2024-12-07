#include "utilities.hpp"

#include <gtest/gtest.h>

TEST(DecompressBase64, HelloWorld) {
  std::string input(hello_world);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::BASE64));
}

TEST(DecompressBase64, AllASCII) {
  std::string input(all_ascii);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::BASE64));
}

TEST(DecompressBase64, JSON) {
  std::string input(temp_json);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::BASE64));
}

TEST(DecompressBase64, JSONFloat) {
  std::string input(temp_json_float);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::BASE64));
}
