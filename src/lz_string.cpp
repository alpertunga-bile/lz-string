#include "lz_string.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <functional>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>

/*
 * --------------------------------------------------------------------------------------------------
 * -- Forward declaration of internal functions
 */

std::u16string _compress(std::u16string_view, uint8_t,
                         const std::function<std::u16string(uint32_t)> &);

std::u16string _decompress(size_t, uint32_t,
                           const std::function<uint16_t(size_t)> &);

/*
 * --------------------------------------------------------------------------------------------------
 * -- Helper functions
 */

constexpr uint32_t char_code_at(std::u16string_view str, int index) {
  return static_cast<uint32_t>(str.at(index));
}

std::u16string join_array(const std::vector<std::u16string> &vec) {
  return std::accumulate(
      vec.begin(), vec.end(), std::u16string{},
      [](const std::u16string &a, const std::u16string &b) { return a + b; });
}

std::u16string from_char_code(uint32_t value) {
  return {static_cast<char16_t>(value)};
}

const std::u16string key_base_64 =
    u"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

const std::u16string key_uri_safe =
    u"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-$";

std::unordered_map<std::u16string, std::unordered_map<char16_t, uint16_t>>
    base_reverse_dict = {};

uint16_t get_base_value(const std::u16string &alphabet, char16_t character) {
  if (!base_reverse_dict.contains(alphabet)) {
    size_t alphabet_length = alphabet.length();

    for (size_t i = 0; i < alphabet_length; ++i) {
      base_reverse_dict[alphabet][alphabet.at(i)] = static_cast<uint16_t>(i);
    }
  }

  return base_reverse_dict[alphabet][character];
}

std::u16string convert_from_uint8_array(const std::vector<uint8_t>& data) {
  size_t length = std::floor(data.size() / 2);
  std::vector<std::u16string> result(length);

  for(int i = 0; i < length; ++i) {
    result.push_back(from_char_code(data[i * 2] * 256 + data [i * 2 + 1]));
  }

  if(data.size() & 1u) {
    result.push_back(from_char_code(data[data.size() - 1] * 256));
  }

  return join_array(result);
}

/*
 * --------------------------------------------------------------------------------------------------
 * -- Public function declarations
 */

namespace pxd::lz_string {

std::u16string compress(std::u16string_view input) {
  if (input.empty()) {
    return {u""};
  }

  return _compress(input, 16, [](uint32_t c) {
    return std::u16string(1, static_cast<char16_t>(c));
  });
}

std::u16string decompress(std::u16string_view input) {
  if (input.empty()) {
    return u"";
  }

  return _decompress(input.length(), 32768, [input](size_t index) {
    return static_cast<uint16_t>(input.at(index));
  });
}

std::u16string compressUTF16(std::u16string_view input) {
  if (input.empty()) {
    return u"";
  }

  return _compress(input, 15,
                   [](uint32_t a) {
                     return std::u16string(1, static_cast<char16_t>(a + 32u));
                   }) +
         u" ";
}

std::u16string decompressUTF16(std::u16string_view input) {
  if (input.empty()) {
    return u"";
  }

  return _decompress(input.length(), 16384, [input](size_t index) {
    return static_cast<uint16_t>(input.at(index)) - 32u;
  });
}

std::u16string compressBase64(std::u16string_view input) {
  if (input.empty()) {
    return u"";
  }

  std::u16string result = _compress(input, 6, [](uint32_t a) {
    return std::u16string(1, key_base_64.at(a));
  });

  size_t result_modulo = result.length() % 4;

  switch (result_modulo) {
  case 0:
    return result;
  case 1:
    return result + u"===";
  case 2:
    return result + u"==";
  case 3:
    return result + u"=";
  default:
    return result;
  }
}

std::u16string decompressBase64(std::u16string_view input) {
  if (input.empty()) {
    return u"";
  }

  return _decompress(input.length(), 32, [input](size_t index) {
    return get_base_value(key_base_64, input.at(index));
  });
}

std::u16string compressEncodedURI(std::u16string_view input) {
  if (input.empty()) {
    return u"";
  }

  return _compress(input, 6, [](uint32_t a) {
    return std::u16string(1, key_uri_safe.at(a));
  });
}

std::u16string decompressEncodedURI(std::u16string_view input) {
  if (input.empty()) {
    return u"";
  }

  std::u16string str(input);
  std::replace(str.begin(), str.end(), u' ', u'+');
  std::u16string_view replaced_view = str;

  return _decompress(replaced_view.length(), 32, [replaced_view](size_t index) {
    return get_base_value(key_uri_safe, replaced_view.at(index));
  });
}

auto compressUint8Array(std::u16string_view input) -> std::vector<uint8_t> {
  if(input.empty()) {
    return {};
  }

  std::u16string compressed = compress(input);
  std::vector<uint8_t> result(compressed.length() * 2);
  const size_t compressed_length = compressed.length();

  for(int i = 0; i < compressed_length; ++i) {
    auto current_value = static_cast<uint16_t>(char_code_at(compressed, i));

    result[i * 2u] = current_value >> 8u;
    result[i * 2u + 1u] = current_value % 256u;
  }

  return result;
}

auto decompressUint8Array(const std::vector<uint8_t>& input) -> std::u16string {
  if(input.size() == 0) {
    return u"";
  }

  return decompress(convert_from_uint8_array(input));
}

} // namespace pxd::lz_string

/*
 * --------------------------------------------------------------------------------------------------
 * -- Compress internal function
 */

std::u16string
_compress(std::u16string_view uncompressed_str, uint8_t bits_per_char,
          const std::function<std::u16string(uint32_t)> &get_char_from_int) {

  if (uncompressed_str.empty()) {
    return u"";
  }

  uint32_t value = 0;

  std::unordered_map<std::u16string, uint32_t> context_dictionary = {};
  std::unordered_set<std::u16string> context_set_to_create = {};

  std::u16string context_c = {};
  std::u16string context_wc = {};
  std::u16string context_w = {};

  uint32_t context_enlarge_in = 2;
  uint32_t context_dict_size = 3;
  uint8_t context_numbits = 2;

  std::vector<std::u16string> context_data;
  uint32_t context_data_val = 0;
  uint32_t context_data_position = 0;

  const size_t uncompressed_length = uncompressed_str.length();

  for (size_t ii = 0; ii < uncompressed_length; ++ii) {
    context_c = uncompressed_str.at(ii);

    if (!context_dictionary.contains(context_c)) {
      context_dictionary[context_c] = context_dict_size++;
      context_set_to_create.insert(context_c);
    }

    context_wc = context_w + context_c;

    if (context_dictionary.contains(context_wc)) {
      context_w = context_wc;
    } else {
      if (context_set_to_create.contains(context_w)) {
        if (char_code_at(context_w, 0) < 256) {
          for (int i = 0; i < context_numbits; ++i) {
            context_data_val = context_data_val << 1u;

            if (context_data_position != bits_per_char - 1) {
              context_data_position++;
              continue;
            }

            context_data_position = 0;
            context_data.push_back(get_char_from_int(context_data_val));
            context_data_val = 0;
          }

          value = char_code_at(context_w, 0);

          for (int i = 0; i < 8; i++) {
            context_data_val = (context_data_val << 1u) | (value & 1u);
            value = value >> 1u;

            if (context_data_position != bits_per_char - 1) {
              context_data_position++;
              continue;
            }

            context_data_position = 0;
            context_data.push_back(get_char_from_int(context_data_val));
            context_data_val = 0;
          }
        } else {
          value = 1;

          for (int i = 0; i < context_numbits; ++i) {
            context_data_val = (context_data_val << 1u) | value;
            value = 0;

            if (context_data_position != bits_per_char - 1) {
              context_data_position++;
              continue;
            }

            context_data_position = 0;
            context_data.push_back(get_char_from_int(context_data_val));
            context_data_val = 0;
          }

          value = char_code_at(context_w, 0);

          for (int i = 0; i < 16; ++i) {
            context_data_val = (context_data_val << 1) | (value & 1);
            value = value >> 1u;

            if (context_data_position != bits_per_char - 1) {
              context_data_position++;
            } else {
              context_data_position = 0;
              context_data.push_back(get_char_from_int(context_data_val));
              context_data_val = 0;
            }
          }
        }

        context_enlarge_in--;
        if (context_enlarge_in == 0) {
          context_enlarge_in =
              static_cast<uint32_t>(std::pow(2, context_numbits));
          context_numbits++;
        }

        context_set_to_create.erase(context_w);
      } else {
        value = context_dictionary[context_w];

        for (int i = 0; i < context_numbits; ++i) {
          context_data_val = (context_data_val << 1) | (value & 1);
          value = value >> 1u;

          if (context_data_position != bits_per_char - 1) {
            context_data_position++;
            continue;
          }

          context_data_position = 0;
          context_data.push_back(get_char_from_int(context_data_val));
          context_data_val = 0;
        }
      }

      context_enlarge_in--;
      if (context_enlarge_in == 0) {
        context_enlarge_in =
            static_cast<uint32_t>(std::pow(2, context_numbits));
        context_numbits++;
      }

      context_dictionary[context_wc] = context_dict_size++;
      context_w = context_c;
    }
  }

  if (context_w.compare(u"") != 0) {
    if (context_set_to_create.contains(context_w)) {
      if (char_code_at(context_w, 0) < 256) {
        for (int i = 0; i < context_numbits; ++i) {
          if (context_data_position != bits_per_char - 1) {
            context_data_position++;
            continue;
          }

          context_data_position = 0;
          context_data.push_back(get_char_from_int(context_data_val));
          context_data_val = 0;
        }

        value = char_code_at(context_w, 0);

        for (int i = 0; i < 8; ++i) {
          context_data_val = (context_data_val << 1) | (value & 1);
          value = value >> 1u;

          if (context_data_position != bits_per_char - 1) {
            context_data_position++;
            continue;
          }

          context_data_position = 0;
          context_data.push_back(get_char_from_int(context_data_val));
          context_data_val = 0;
        }
      } else {
        value = 1;

        for (int i = 0; i < context_numbits; ++i) {
          context_data_val = (context_data_val << 1) | value;
          value = 0;

          if (context_data_position != bits_per_char - 1) {
            context_data_position++;
            continue;
          }

          context_data_position = 0;
          context_data.push_back(get_char_from_int(context_data_val));
          context_data_val = 0;
        }

        value = char_code_at(context_w, 0);

        for (int i = 0; i < 16; ++i) {
          context_data_val = (context_data_val << 1) | (value & 1);

          if (context_data_position != bits_per_char - 1) {
            context_data_position++;
            continue;
          }

          context_data_position = 0;
          context_data.push_back(get_char_from_int(context_data_val));
          context_data_val = 0;
        }
      }

      context_enlarge_in--;
      if (context_enlarge_in == 0) {
        context_enlarge_in =
            static_cast<uint32_t>(std::pow(2, context_numbits));
        context_numbits++;
      }

      context_set_to_create.erase(context_w);
    } else {
      value = context_dictionary[context_w];

      for (int i = 0; i < context_numbits; ++i) {
        context_data_val = (context_data_val << 1) | (value & 1);
        value = value >> 1;

        if (context_data_position != bits_per_char - 1) {
          context_data_position++;
          continue;
        }

        context_data_position = 0;
        context_data.push_back(get_char_from_int(context_data_val));
        context_data_val = 0;
      }
    }

    context_enlarge_in--;
    if (context_enlarge_in == 0) {
      context_enlarge_in = static_cast<uint32_t>(std::pow(2, context_numbits));
      context_numbits++;
    }
  }

  value = 2;

  for (int i = 0; i < context_numbits; ++i) {
    context_data_val = (context_data_val << 1) | (value & 1);
    value = value >> 1;

    if (context_data_position != bits_per_char - 1) {
      context_data_position++;
      continue;
    }

    context_data_position = 0;
    context_data.push_back(get_char_from_int(context_data_val));
    context_data_val = 0;
  }

  bool loop = true;

  do {
    context_data_val = context_data_val << 1;

    if (context_data_position != bits_per_char - 1) {
      context_data_position++;
      continue;
    }

    context_data.push_back(get_char_from_int(context_data_val));
    loop = false;
  } while (loop);

  std::u16string result = join_array(context_data);

  return result;
}

/*
 * --------------------------------------------------------------------------------------------------
 * -- Decompress internal function
 */

struct DecompressionTracker {
  uint16_t value;
  uint32_t position;
  uint32_t index;
};

uint32_t calculate_bits(DecompressionTracker &data, uint32_t power,
                        uint32_t max_power_upper, uint32_t reset_value,
                        const std::function<uint16_t(size_t)> &get_next_value) {
  uint32_t bits = 0;
  uint32_t max_power = static_cast<uint32_t>(std::pow(2, max_power_upper));

  while (power != max_power) {
    uint32_t resb = data.value & data.position;

    data.position >>= 1;

    if (data.position == 0) {
      data.position = reset_value;
      data.value = get_next_value(data.index++);
    }

    bits |= (resb > 0 ? 1 : 0) * power;
    power <<= 1;
  }

  return bits;
}

std::u16string
_decompress(size_t length, uint32_t reset_value,
            const std::function<uint16_t(size_t)> &get_next_value) {
  std::vector<std::u16string> dictionary = {u"0", u"1", u"2"};
  std::vector<std::u16string> result(length);

  DecompressionTracker data = {get_next_value(0), reset_value, 1};

  uint32_t enlarge_in = 4;
  uint32_t num_bits = 3;

  std::u16string entry = u"";

  std::u16string c = u"";
  uint32_t c_number = 0;

  uint32_t bits = calculate_bits(data, 1, 2, reset_value, get_next_value);

  switch (bits) {
  case 0:
    bits = calculate_bits(data, 1, 8, reset_value, get_next_value);
    c = from_char_code(bits);
    break;
  case 1:
    bits = calculate_bits(data, 1, 16, reset_value, get_next_value);
    c = from_char_code(bits);
    break;

  case 2:
    return u"";
  }

  if (c.compare(u"") == 0) {
    return u"";
  }

  dictionary.push_back(c);
  std::u16string w = c;
  result.push_back(c);

  while (true) {
    if (data.index > length) {
      return u"";
    }

    bits = calculate_bits(data, 1, num_bits, reset_value, get_next_value);
    c_number = bits;

    switch (bits) {
    case 0:
      bits = calculate_bits(data, 1, 8, reset_value, get_next_value);
      dictionary.push_back(from_char_code(bits));
      c_number = static_cast<uint32_t>(dictionary.size()) - 1;
      enlarge_in--;
      break;
    case 1:
      bits = calculate_bits(data, 1, 16, reset_value, get_next_value);
      dictionary.push_back(from_char_code(bits));
      c_number = static_cast<uint32_t>(dictionary.size()) - 1;
      enlarge_in--;
      break;
    case 2:
      return join_array(result);
    }

    if (enlarge_in == 0) {
      enlarge_in = static_cast<uint32_t>(std::pow(2, num_bits));
      num_bits++;
    }

    if (dictionary.size() > c_number && !dictionary[c_number].empty()) {
      entry = dictionary[c_number];
    } else {
      if (c_number == dictionary.size()) {
        entry = w + w.at(0);
      } else {
        return u"";
      }
    }

    result.push_back(entry);

    dictionary.push_back(w + entry.at(0));
    enlarge_in--;
    w = entry;

    if (enlarge_in == 0) {
      enlarge_in = static_cast<uint32_t>(std::pow(2, num_bits));
      num_bits++;
    }
  }

  return u"";
}
