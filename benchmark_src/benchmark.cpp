#include <benchmark/benchmark.h>

#include "../src/lz_string.hpp"
#include "../test_src/utilities.hpp"

/*

static std::string hello_world =
    get_text_file_content("test_src/data/hello_world_str/data.bin");
static std::string all_ascii =
    get_text_file_content("test_src/data/all_ascii_str/data.bin");
static std::string temp_json =
    get_text_file_content("test_src/data/temp_json/data.bin");
static std::string temp_json_float =
    get_text_file_content("test_src/data/temp_json_float/data.bin");

constexpr size_t NUM_ITER = 100000;


#define MAKE_COMPRESS_BENCHMARK(input_name)                      \
  static void BM_compress_##input_name(benchmark::State &state) { \
    auto input = pxd::lz_string::to_utf16(input_name);           \
                                                                 \
    for (auto _ : state) {                                       \
      auto compressed = pxd::lz_string::compress(input);         \
    }                                                            \
  }                                                               \
  BENCHMARK(BM_compress_##input_name)->Iterations(NUM_ITER);

#define MAKE_DECOMPRESS_BENCHMARK(input_name)                     \
  static void BM_compress_##input_name(benchmark::State &state) { \
    auto compressed = pxd::lz_string::compress(                   \
        pxd::lz_string::to_utf16(std::string(input_name)));       \
                                                                  \
    for (auto _ : state) {                                        \
      auto decompressed = pxd::lz_string::decompress(compressed); \
    }                                                             \
  }                                                               \
  BENCHMARK(BM_decompressinput_name##)->Iterations(NUM_ITER);

MAKE_COMPRESS_BENCHMARK(hello_world);

*/