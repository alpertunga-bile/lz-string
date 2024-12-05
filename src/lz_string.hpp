#ifndef _LZ_STRING_MODERN_LZ_STRING_HPP
#define _LZ_STRING_MODERN_LZ_STRING_HPP

#include <string>

namespace pxd::lz_string {

constexpr inline std::string to_utf8(std::u16string_view value) {
  return {value.begin(), value.end()};
}

constexpr inline std::u16string to_utf16(std::string_view value) {
  return {value.begin(), value.end()};
}

std::u16string compress(std::u16string_view input);

} // namespace pxd::lz_string

#endif