#ifndef _PXD_LZ_STRING_HPP
#define _PXD_LZ_STRING_HPP

#include <string>

namespace pxd::lz_string {

constexpr inline std::string to_utf8(std::u16string_view value) {
  return {value.begin(), value.end()};
}

constexpr inline std::u16string to_utf16(std::string_view value) {
  return {value.begin(), value.end()};
}

std::u16string compress(std::u16string_view input);
std::u16string decompress(std::u16string_view input);

std::u16string compressUTF16(std::u16string_view input);
std::u16string decompressUTF16(std::u16string_view input);

std::u16string compressBase64(std::u16string_view input);
std::u16string decompressBase64(std::u16string_view input);

std::u16string compressEncodedURI(std::u16string_view input);
std::u16string decompressEncodedURI(std::u16string_view input);

} // namespace pxd::lz_string

#endif