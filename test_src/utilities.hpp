#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

enum class LZStringOptions {
  INVALID_UTF16,
  VALID_UTF16,
  BASE64,
  URI,
  UINT8ARRAY
};

std::string           get_text_file_content(std::string_view filename);
std::u16string        get_utf16_text_file_content(std::string_view filename);
std::vector<uint8_t>  get_bin_file_content(std::string_view filename);
std::vector<uint16_t> get_utf16_bin_file_content(std::string_view filename);

std::tuple<std::string, std::vector<uint16_t>>
get_compress_test_variables(std::string_view test_name, LZStringOptions option);

std::u16string get_compressed(std::string_view value, LZStringOptions option);

std::u16string get_decompressed(std::u16string_view value,
                                LZStringOptions     option);

bool compare_u16(LZStringOptions option, std::string_view input,
                 const std::vector<uint16_t> &result);

bool compare_u16(std::string_view input, LZStringOptions option);

constexpr char hello_world[16] = "Hello World !!!";
constexpr char all_ascii[96]   = " !\"#$%&'()*+,-./"
                                 "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]"
                                 "^_`abcdefghijklmnopqrstuvwxyz{|}~";
constexpr char temp_json[336] =
    "{\"string\":\"Hello, "
    "World!\",\"number\":123,\"boolean\":true,\"null\":null,\"array\":[1,2,3,"
    "4,5],\"object\":{\"name\":\"John "
    "Doe\",\"age\":30,\"occupation\":\"Software "
    "Developer\"},\"nested_object\":{\"address\":{\"street\":\"123 Main "
    "St\",\"city\":\"Anytown\",\"state\":\"CA\",\"zip\":\"12345\"}},\"array_"
    "of_objects\":[{\"name\":\"Jane Doe\",\"age\":25},{\"name\":\"Bob "
    "Smith\",\"age\":40}]}";
constexpr char temp_json_float[225] =
    "{\"float\":3.14159,\"double\":2.71828,\"negativeFloat\":-0.12345,"
    "\"exponentialFloat\":0.000123,\"arrayOfFloats\":[1.1,2.2,3.3,4.4,5.5],"
    "\"objectWithFloats\":{\"pi\":3.14159,\"e\":2.71828},"
    "\"nestedObjectWithFloats\":{\"point\":{\"x\":1.1,\"y\":2.2}}}";
