#include <benchmark/benchmark.h>

#include "../src/lz_string.hpp"
#include "../test_src/utilities.hpp"

constexpr size_t NUM_ITER = 100000;

#define MAKE_COMPRESS_BENCHMARK(compress_func_name, input_name)           \
  static void BM_##compress_func_name##_##input_name##(benchmark::State & \
                                                       state) {           \
    auto input = pxd::lz_string::to_utf16(std::string(hello_world));      \
                                                                          \
    for (auto _ : state) {                                                \
      auto compressed = pxd::lz_string::##compress_func_name##(input);    \
    }                                                                     \
  }                                                                       \
  BENCHMARK(BM_##compress_func_name##_##input_name##)->Iterations(NUM_ITER);

#define MAKE_DECOMPRESS_BENCHMARK(compress_func_name, decompress_func_name, \
                                  input_name)                               \
  static void BM_##decompress_func_name##_##input_name##(benchmark::State & \
                                                         state) {           \
    auto compressed = pxd::lz_string::##compress_func_name##(               \
        pxd::lz_string::to_utf16(std::string(input_name)));                 \
                                                                            \
    for (auto _ : state) {                                                  \
      auto decompressed =                                                   \
          pxd::lz_string::##decompress_func_name##(compressed);             \
    }                                                                       \
  }                                                                         \
  BENCHMARK(BM_##decompress_func_name##_##input_name##)->Iterations(NUM_ITER);

MAKE_COMPRESS_BENCHMARK(compress, hello_world);
MAKE_COMPRESS_BENCHMARK(compressUTF16, hello_world);
MAKE_COMPRESS_BENCHMARK(compressBase64, hello_world);
MAKE_COMPRESS_BENCHMARK(compressEncodedURI, hello_world);
MAKE_COMPRESS_BENCHMARK(compressUint8Array, hello_world);

MAKE_COMPRESS_BENCHMARK(compress, all_ascii);
MAKE_COMPRESS_BENCHMARK(compressUTF16, all_ascii);
MAKE_COMPRESS_BENCHMARK(compressBase64, all_ascii);
MAKE_COMPRESS_BENCHMARK(compressEncodedURI, all_ascii);
MAKE_COMPRESS_BENCHMARK(compressUint8Array, all_ascii);

MAKE_COMPRESS_BENCHMARK(compress, temp_json);
MAKE_COMPRESS_BENCHMARK(compressUTF16, temp_json);
MAKE_COMPRESS_BENCHMARK(compressBase64, temp_json);
MAKE_COMPRESS_BENCHMARK(compressEncodedURI, temp_json);
MAKE_COMPRESS_BENCHMARK(compressUint8Array, temp_json);

MAKE_COMPRESS_BENCHMARK(compress, temp_json_float);
MAKE_COMPRESS_BENCHMARK(compressUTF16, temp_json_float);
MAKE_COMPRESS_BENCHMARK(compressBase64, temp_json_float);
MAKE_COMPRESS_BENCHMARK(compressEncodedURI, temp_json_float);
MAKE_COMPRESS_BENCHMARK(compressUint8Array, temp_json_float);

MAKE_DECOMPRESS_BENCHMARK(compress, decompress, hello_world);
MAKE_DECOMPRESS_BENCHMARK(compressUTF16, decompressUTF16, hello_world);
MAKE_DECOMPRESS_BENCHMARK(compressBase64, decompressBase64, hello_world);
MAKE_DECOMPRESS_BENCHMARK(compressEncodedURI, decompressEncodedURI,
                          hello_world);
MAKE_DECOMPRESS_BENCHMARK(compressUint8Array, decompressUint8Array,
                          hello_world);

MAKE_DECOMPRESS_BENCHMARK(compress, decompress, all_ascii);
MAKE_DECOMPRESS_BENCHMARK(compressUTF16, decompressUTF16, all_ascii);
MAKE_DECOMPRESS_BENCHMARK(compressBase64, decompressBase64, all_ascii);
MAKE_DECOMPRESS_BENCHMARK(compressEncodedURI, decompressEncodedURI, all_ascii);
MAKE_DECOMPRESS_BENCHMARK(compressUint8Array, decompressUint8Array, all_ascii);

MAKE_DECOMPRESS_BENCHMARK(compress, decompress, temp_json);
MAKE_DECOMPRESS_BENCHMARK(compressUTF16, decompressUTF16, temp_json);
MAKE_DECOMPRESS_BENCHMARK(compressBase64, decompressBase64, temp_json);
MAKE_DECOMPRESS_BENCHMARK(compressEncodedURI, decompressEncodedURI, temp_json);
MAKE_DECOMPRESS_BENCHMARK(compressUint8Array, decompressUint8Array, temp_json);

MAKE_DECOMPRESS_BENCHMARK(compress, decompress, temp_json_float);
MAKE_DECOMPRESS_BENCHMARK(compressUTF16, decompressUTF16, temp_json_float);
MAKE_DECOMPRESS_BENCHMARK(compressBase64, decompressBase64, temp_json_float);
MAKE_DECOMPRESS_BENCHMARK(compressEncodedURI, decompressEncodedURI,
                          temp_json_float);
MAKE_DECOMPRESS_BENCHMARK(compressUint8Array, decompressUint8Array,
                          temp_json_float);

BENCHMARK_MAIN();