#include "utilities.hpp"

#include <gtest/gtest.h>

constexpr LZStringOptions compression = LZStringOptions::VALID_UTF16;

#define MAKE_DECOMPRESS_TEST(test_name, test_data_name)                   \
  TEST(DecompressUTF16, test_name) {                                      \
    EXPECT_TRUE(get_decompress_test_result(test_data_name, compression)); \
  }

MAKE_DECOMPRESS_TEST(AllASCII, "all_ascii")
MAKE_DECOMPRESS_TEST(HelloWorld, "hello_world")
MAKE_DECOMPRESS_TEST(LoremIpsum, "lorem_ipsum")
MAKE_DECOMPRESS_TEST(PI, "pi")
MAKE_DECOMPRESS_TEST(Repeated, "repeated")
MAKE_DECOMPRESS_TEST(Tattoo, "tattoo")
MAKE_DECOMPRESS_TEST(JSON, "temp_json")
MAKE_DECOMPRESS_TEST(JSONFloat, "temp_json_float")
