#ifndef _PXD_LZ_STRING_HPP
#define _PXD_LZ_STRING_HPP

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace pxd::lz_string {

auto to_utf8(std::u16string_view value) -> std::string;
auto to_utf16(std::string_view value) -> std::u16string;

auto compress(std::u16string_view input) -> std::u16string;
auto decompress(std::u16string_view input) -> std::u16string;

auto compressUTF16(std::u16string_view input) -> std::u16string;
auto decompressUTF16(std::u16string_view input) -> std::u16string;

auto compressBase64(std::u16string_view input) -> std::u16string;
auto decompressBase64(std::u16string_view input) -> std::u16string;

auto compressEncodedURI(std::u16string_view input) -> std::u16string;
auto decompressEncodedURI(std::u16string_view input) -> std::u16string;

auto compressUint8Array(std::u16string_view input) -> std::vector<uint8_t>;
auto decompressUint8Array(const std::vector<uint8_t> &input) -> std::u16string;

} // namespace pxd::lz_string

#endif
