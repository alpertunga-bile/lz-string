#include "utilities.hpp"

#include "../includes/lz_string.hpp"
#include <algorithm>
#include <gtest/gtest.h>

constexpr LZStringOptions compression = LZStringOptions::UINT8ARRAY;

#define MAKE_COMPRESS_TEST(test_name, test_data_name)                          \
  TEST(CompressUint8Array, test_name)                                          \
  {                                                                            \
    auto [input, result] =                                                     \
      get_compress_test_variables(test_data_name, compression);                \
                                                                               \
    std::vector<uint8_t> compressed =                                          \
      pxd::lz_string::compressUint8Array(pxd::lz_string::to_utf16(input));     \
                                                                               \
    std::vector<uint16_t> compressed_utf16(compressed.begin(),                 \
                                           compressed.end());                  \
                                                                               \
    bool is_equal =                                                            \
      std::equal(result.begin(), result.end(), compressed_utf16.begin());      \
                                                                               \
    EXPECT_TRUE(is_equal);                                                     \
  }

MAKE_COMPRESS_TEST(AllASCII, "all_ascii")
MAKE_COMPRESS_TEST(HelloWorld, "hello_world")
MAKE_COMPRESS_TEST(LoremIpsum, "lorem_ipsum")
MAKE_COMPRESS_TEST(PI, "pi")
MAKE_COMPRESS_TEST(Repeated, "repeated")
MAKE_COMPRESS_TEST(Tattoo, "tattoo")
MAKE_COMPRESS_TEST(JSON, "temp_json")
MAKE_COMPRESS_TEST(JSONFloat, "temp_json_float")