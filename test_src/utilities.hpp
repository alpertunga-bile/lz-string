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

bool get_decompress_test_result(std::string_view test_name,
                                LZStringOptions  option);

std::tuple<std::string, std::vector<uint16_t>>
get_compress_test_variables(std::string_view test_name, LZStringOptions option);

std::u16string get_compressed(std::string_view value, LZStringOptions option);

std::u16string get_decompressed(std::u16string_view value,
                                LZStringOptions     option);

bool compare_u16(LZStringOptions option, std::string_view input,
                 const std::vector<uint16_t> &result);

bool compare_u16(std::string_view input, LZStringOptions option);