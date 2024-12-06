#include "src/lz_string.hpp"

#include <algorithm>
#include <vector>

#include <gtest/gtest.h>

enum class LZStringOptions { INVALID_UTF16, VALID_UTF16, BASE64, URI };

std::u16string get_compressed(std::string_view value, LZStringOptions option) {
  switch (option) {
  case LZStringOptions::INVALID_UTF16:
    return pxd::lz_string::compress(pxd::lz_string::to_utf16(value));
  case LZStringOptions::VALID_UTF16:
    return pxd::lz_string::compressUTF16(pxd::lz_string::to_utf16(value));
  case LZStringOptions::BASE64:
    return pxd::lz_string::compressBase64(pxd::lz_string::to_utf16(value));
  case LZStringOptions::URI:
    return pxd::lz_string::compressEncodedURI(pxd::lz_string::to_utf16(value));
  default:
    return u"";
  }
}

std::u16string get_decompressed(std::string_view value,
                                LZStringOptions option) {
  switch (option) {
  case LZStringOptions::INVALID_UTF16:
    return pxd::lz_string::decompress(pxd::lz_string::to_utf16(value));
  case LZStringOptions::VALID_UTF16:
    return pxd::lz_string::decompressUTF16(pxd::lz_string::to_utf16(value));
  case LZStringOptions::BASE64:
    return pxd::lz_string::decompressBase64(pxd::lz_string::to_utf16(value));
  case LZStringOptions::URI:
    return pxd::lz_string::decompressEncodedURI(
        pxd::lz_string::to_utf16(value));
  default:
    return u"";
  }
}

bool compare_u16(LZStringOptions option, std::string_view input,
                 const std::vector<uint16_t> &result) {
  std::u16string compressed = get_compressed(input, option);

  std::vector<uint16_t> compress_result = {};
  const size_t length = compressed.length();

  for (int i = 0; i < length; ++i) {
    compress_result.push_back(static_cast<uint16_t>(compressed.at(i)));
  }

  if (compress_result.size() != result.size()) {
    return false;
  }

  return std::equal(compress_result.begin(), compress_result.end(),
                    result.begin());
}

constexpr char hello_world[16] = "Hello World !!!";
constexpr char all_ascii[94] =
    "!#$%&'()*+,-./"
    "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`"
    "abcdefghijklmnopqrstuvwxyz{|}~\\";
constexpr char temp_json[336] =
    "{\"string\":\"Hello, "
    "World!\",\"number\":123,\"boolean\":true,\"null\":null,\"array\":[1,2,3,"
    "4,5],\"object\":{\"name\":\"John "
    "Doe\",\"age\":30,\"occupation\":\"Software "
    "Developer\"},\"nested_object\":{\"address\":{\"street\":\"123 Main "
    "St\",\"city\":\"Anytown\",\"state\":\"CA\",\"zip\":\"12345\"}},\"array_"
    "of_objects\":[{\"name\":\"Jane Doe\",\"age\":25},{\"name\":\"Bob "
    "Smith\",\"age\":40}]}";
constexpr char temp_json_float[224] =
    "{\"float\":3.14159,\"double\":2.71828,\"negativeFloat\":-0.12345,"
    "\"exponentialFloat\":1.23e-4,\"arrayOfFloats\":[1.1,2.2,3.3,4.4,5.5],"
    "\"objectWithFloats\":{\"pi\":3.14159,\"e\":2.71828},"
    "\"nestedObjectWithFloats\":{\"point\":{\"x\":1.1,\"y\":2.2}}}";

TEST(Compress, HelloWorld) {
  std::string input(hello_world);

  std::vector<uint16_t> result = {1157,  12342, 24822, 64,   60048,
                                  10032, 1242,  1056,  53248};

  EXPECT_TRUE(compare_u16(LZStringOptions::INVALID_UTF16, input, result));
}

TEST(Compres, AllASCII) {
  std::string input(all_ascii);

  std::vector<uint16_t> result = {
      8454,  8228,  2624,  25614, 16404, 1184,  5377,  43011, 16474, 464,
      7808,  3074,  12292, 49203, 44,    688,   1728,  15104, 7170,  28677,
      49207, 60,    752,   1984,  16128, 513,   1025,  2054,  4098,  8212,
      16408, 32881, 18,    292,   328,   1680,  800,   5696,  7296,  30976,
      2561,  5121,  10246, 20482, 40981, 16410, 32885, 26,    308,   360,
      1744,  2976,  3904,  16000, 768,   34304, 17920, 50688, 9728,  42496,
      26112, 58880, 5632,  38400, 22016, 54784, 13824, 46592, 30208, 62976,
      3584,  36352, 19968, 52736, 11776, 44544, 28160, 60928, 7680,  40448,
      24064, 56832, 15872, 48640, 32256, 14912, 0};

  EXPECT_TRUE(compare_u16(LZStringOptions::INVALID_UTF16, input, result));
}

TEST(Compress, JSON) {
  std::string input(temp_json);

  std::vector<uint16_t> result = {
      14210, 8398,  736,   19977, 24694, 1841,  184,   16393, 664,   1739,
      1968,  3328,  1027,  43749, 5632,  38920, 16958, 8640,  11136, 46593,
      6245,  2562,  12292, 49203, 7469,  29410, 49536, 8604,  5328,  6243,
      43207, 2617,  22762, 35461, 5184,  20244, 437,   15334, 61343, 32790,
      31745, 22530, 59861, 49856, 5510,  198,   4178,  33674, 10630, 5152,
      330,   57345, 26384, 32776, 44603, 45698, 15282, 12032, 805,   40349,
      33536, 936,   33804, 11780, 43520, 12974, 25,    33792, 15242, 34336,
      17920, 7094,  11836, 31496, 47,    44166, 9222,  1280,  16021, 44419,
      37768, 10373, 1300,  7512,  15204, 3910,  9130,  3887,  8448,  11432,
      48161, 14947, 40221, 35844, 9898,  32,    39994, 33838, 11844, 40228,
      4728,  18432, 12426, 60680, 23,    35900, 18344, 57737, 46413, 18282,
      34483, 22131, 19901, 33823, 29206, 45995, 33255, 47248, 42001, 2164,
      49704, 28169, 34475, 62320, 30720, 16982, 6547,  4451,  58682, 35009,
      51267, 9290,  42594, 43264};

  EXPECT_TRUE(compare_u16(LZStringOptions::INVALID_UTF16, input, result));
}

TEST(Compress, JSONFloat) {
  std::string input(temp_json_float);

  std::vector<uint16_t> result = {
      14210, 8294,  864,   62984, 24622, 8215,  408,   1856,  17920, 45984,
      44036, 57350, 33792, 19616, 5568,  8968,  1330,  16422, 21511, 26432,
      3642,  23072, 15210, 1847,  32843, 110,   54273, 35655, 33920, 11520,
      1548,  30098, 25028, 23168, 3840,  3665,  47731, 36806, 1073,  45074,
      9629,  13562, 31044, 24578, 29363, 39,    32889, 12295, 57350, 29248,
      7005,  1538,  3304,  4934,  16420, 50500, 49185, 50497, 49157, 53794,
      32928, 694,   40966, 13184, 1879,  58240, 177,   29575, 29765, 855,
      57923, 17093, 50209, 1444,  16486, 25441, 24581, 62182, 42355, 34470,
      8304,  20043, 18638, 53013, 51776, 10887, 59095, 59649, 21062, 63298,
      9143,  42307, 41903, 39424};

  EXPECT_TRUE(compare_u16(LZStringOptions::INVALID_UTF16, input, result));
}