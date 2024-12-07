#include "utilities.hpp"

#include <gtest/gtest.h>

TEST(DecompressURI, HelloWorld) {
  std::string input(hello_world);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::URI));
}

TEST(DecompressURI, AllASCII) {
  std::string input(all_ascii);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::URI));
}

TEST(DecompressURI, JSON) {
  std::string input(temp_json);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::URI));
}

TEST(DecompressURI, JSONFloat) {
  std::string input(temp_json_float);

  EXPECT_TRUE(compare_u16(input, LZStringOptions::URI));
}
