#include "utilities.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>

#include "../src/lz_string.hpp"

std::string get_text_file_content(std::string_view filename) {
  std::ifstream file(filename.data());

  if (!file.is_open()) {
    return "";
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  file.close();

  return buffer.str();
}

std::u16string get_utf16_text_file_content(std::string_view filename) {
  auto content = get_bin_file_content(filename);

  return pxd::lz_string::from_uint8array(get_bin_file_content(filename));
}

std::vector<uint8_t> get_bin_file_content(std::string_view filename) {
  std::ifstream file(filename.data(), std::ios::binary);

  if (!file.is_open()) {
    return {};
  }

  return {std::istreambuf_iterator<char>(file), {}};
}

std::vector<uint16_t> get_utf16_bin_file_content(std::string_view filename) {
  std::u16string content = get_utf16_text_file_content(filename);

  return {content.begin(), content.end()};
}

std::tuple<std::string, std::vector<uint16_t>>
get_compress_test_variables(std::string_view test_name,
                            LZStringOptions  option) {

  std::string data_folder_path =
      std::string("test_src/data/") + test_name.data();

  std::string data = get_text_file_content(data_folder_path + "/data.bin");

  switch (option) {
  case LZStringOptions::INVALID_UTF16: {
    std::vector<uint16_t> content =
        get_utf16_bin_file_content(data_folder_path + "/invalid_utf16.bin");
    return {data, content};
  }
  case LZStringOptions::VALID_UTF16: {
    std::vector<uint16_t> content =
        get_utf16_bin_file_content(data_folder_path + "/valid_utf16.bin");
    return {data, content};
  }
  case LZStringOptions::BASE64: {
    std::vector<uint8_t> content =
        get_bin_file_content(data_folder_path + "/base64.bin");
    return {data, {content.begin(), content.end()}};
  }
  case LZStringOptions::URI: {
    std::vector<uint8_t> content =
        get_bin_file_content(data_folder_path + "/uri.bin");
    return {data, {content.begin(), content.end()}};
  }
  case LZStringOptions::UINT8ARRAY: {
    std::vector<uint8_t> content =
        get_bin_file_content(data_folder_path + "/uint8array.bin");
    return {data, {content.begin(), content.end()}};
  }
  default:
    return {};
  }
}

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

std::u16string get_decompressed(std::u16string_view value,
                                LZStringOptions     option) {
  switch (option) {
  case LZStringOptions::INVALID_UTF16:
    return pxd::lz_string::decompress(value);
  case LZStringOptions::VALID_UTF16:
    return pxd::lz_string::decompressUTF16(value);
  case LZStringOptions::BASE64:
    return pxd::lz_string::decompressBase64(value);
  case LZStringOptions::URI:
    return pxd::lz_string::decompressEncodedURI(value);
  default:
    return u"";
  }

  return u"";
}

bool compare_u16(LZStringOptions option, std::string_view input,
                 const std::vector<uint16_t> &result) {
  std::u16string compressed = get_compressed(input, option);

  const size_t          length          = compressed.length();
  std::vector<uint16_t> compress_result = {};
  compress_result.reserve(length);

  for (int i = 0; i < length; ++i) {
    compress_result.push_back(static_cast<uint16_t>(compressed.at(i)));
  }

  if (compress_result.size() != result.size()) {
    return false;
  }

  return std::equal(compress_result.begin(), compress_result.end(),
                    result.begin());
}

bool compare_u16(std::string_view input, LZStringOptions option) {
  std::u16string compressed   = get_compressed(input, option);
  std::u16string decompressed = get_decompressed(compressed, option);

  return pxd::lz_string::to_utf16(input) == decompressed;
}
