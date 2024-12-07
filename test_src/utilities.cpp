#include "utilities.hpp"

#include <algorithm>

#include "../src/lz_string.hpp"

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

std::u16string
get_decompressed(std::u16string_view value, LZStringOptions option) {
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


bool compare_u16(std::string_view input, LZStringOptions option) {
  std::u16string compressed = get_compressed(input, option);
  std::u16string decompressed = get_decompressed(compressed, option);

  return pxd::lz_string::to_utf16(input) == decompressed;
}
