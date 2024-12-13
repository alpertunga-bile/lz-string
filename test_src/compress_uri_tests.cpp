#include "utilities.hpp"

#include <gtest/gtest.h>

constexpr LZStringOptions compression = LZStringOptions::URI;

#define MAKE_COMPRESS_TEST(test_name, test_data_name)             \
  TEST(CompressURI, test_name) {                                  \
    auto [input, result] =                                        \
        get_compress_test_variables(test_data_name, compression); \
                                                                  \
    EXPECT_TRUE(compare_u16(compression, input, result));         \
  }

MAKE_COMPRESS_TEST(AllASCII, "all_ascii")
MAKE_COMPRESS_TEST(HelloWorld, "hello_world")
MAKE_COMPRESS_TEST(LoremIpsum, "lorem_ipsum")
MAKE_COMPRESS_TEST(PI, "pi")
MAKE_COMPRESS_TEST(Repeated, "repeated")
MAKE_COMPRESS_TEST(Tattoo, "tattoo")
MAKE_COMPRESS_TEST(JSON, "temp_json")
MAKE_COMPRESS_TEST(JSONFloat, "temp_json_float")