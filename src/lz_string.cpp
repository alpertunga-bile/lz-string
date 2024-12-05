#include "lz_string.hpp"

#include <cmath>
#include <codecvt>
#include <functional>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <string_view>

std::u16string _compress(std::u16string_view, uint8_t,
                         const std::function<std::u16string(uint32_t)> &);

namespace pxd {

std::u16string compress(std::u16string_view input) {
  if (input.length() == 0) {
    return {u""};
  }

  return _compress(input, 16, [](uint32_t c) {
    return std::u16string(1, static_cast<char16_t>(c));
  });
}

} // namespace pxd

constexpr uint32_t char_code_at(std::u16string_view str, int index) {
  return static_cast<uint32_t>(str.at(index));
}

std::u16string
_compress(std::u16string_view uncompressed_str, uint8_t bits_per_char,
          const std::function<std::u16string(uint32_t)> &get_char_from_int) {

  if (uncompressed_str.length() == 0) {
    return {};
  }

  uint32_t value = 0;

  std::unordered_map<std::u16string, uint32_t> context_dictionary = {};
  std::unordered_map<std::u16string, bool> context_dictionary_to_create = {};

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

    if (context_dictionary.contains(context_c)) {
      context_dictionary[context_c] = context_dict_size++;
      context_dictionary_to_create[context_c] = true;
    }

    context_wc = context_w + context_c;

    if (context_dictionary.contains(context_wc)) {
      context_w = context_wc;
      continue;
    }

    if (context_dictionary_to_create.contains(context_w)) {
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

      context_enlarge_in--;
      if (context_enlarge_in == 0) {
        context_enlarge_in =
            static_cast<uint32_t>(std::pow(2, context_numbits));
        context_numbits++;
      }

      context_dictionary_to_create.erase(context_w);
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
      context_enlarge_in = static_cast<uint32_t>(std::pow(2, context_numbits));
      context_numbits++;
    }

    context_dictionary[context_wc] = context_dict_size++;
    context_w = context_c;
  }

  if (context_w.compare(u"") != 0) {
    if (context_dictionary_to_create.contains(context_w)) {
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

      context_dictionary_to_create.erase(context_w);
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

  std::u16string result = std::accumulate(
      context_data.begin(), context_data.end(), std::u16string{},
      [](const std::u16string &a, const std::u16string &b) { return a + b; });

  return result;
}
