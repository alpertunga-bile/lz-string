#include <benchmark/benchmark.h>

#include "../src/lz_string.hpp"
#include "../test_src/utilities.hpp"

#define NUM_ITER 1000

static std::string hello_world =
    get_text_file_content("test_src/data/hello_world_str/data.bin");
static std::string all_ascii =
    get_text_file_content("test_src/data/all_ascii_str/data.bin");
static std::string temp_json =
    get_text_file_content("test_src/data/temp_json/data.bin");
static std::string temp_json_float =
    get_text_file_content("test_src/data/temp_json_float/data.bin");
static std::string lorem_ipsum =
    get_text_file_content("test_src/data/lorem_ipsum/data.bin");
static std::string pi =
    get_text_file_content("test_src/data/pi/data.bin");
static std::string repeated =
    get_text_file_content("test_src/data/repeated/data.bin");
static std::string tattoo =
      get_text_file_content("test_src/data/tattoo/data.bin");

/*
* ---------------------------------------------------------------------------------------------------
* -- Compress benchmarks
*/

#define MAKE_COMPRESS_BENCHMARK(func, inputs) \
static void BM_##func##_##inputs(benchmark::State& state) {     \
  auto input = pxd::lz_string::to_utf16(inputs);                \
                                                                \
 for(auto _ : state) {                                          \
   auto compressed = pxd::lz_string::func(input);               \
 }                                                              \
}                                                               \
BENCHMARK(BM_##func##_##inputs)->Iterations(NUM_ITER);

MAKE_COMPRESS_BENCHMARK(compress, hello_world);
MAKE_COMPRESS_BENCHMARK(compress, all_ascii);
MAKE_COMPRESS_BENCHMARK(compress, temp_json);
MAKE_COMPRESS_BENCHMARK(compress, temp_json_float);
MAKE_COMPRESS_BENCHMARK(compress, lorem_ipsum);
MAKE_COMPRESS_BENCHMARK(compress, pi);
MAKE_COMPRESS_BENCHMARK(compress, repeated);
MAKE_COMPRESS_BENCHMARK(compress, tattoo);

MAKE_COMPRESS_BENCHMARK(compressUTF16, hello_world);
MAKE_COMPRESS_BENCHMARK(compressUTF16, all_ascii);
MAKE_COMPRESS_BENCHMARK(compressUTF16, temp_json);
MAKE_COMPRESS_BENCHMARK(compressUTF16, temp_json_float);
MAKE_COMPRESS_BENCHMARK(compressUTF16, lorem_ipsum);
MAKE_COMPRESS_BENCHMARK(compressUTF16, pi);
MAKE_COMPRESS_BENCHMARK(compressUTF16, repeated);
MAKE_COMPRESS_BENCHMARK(compressUTF16, tattoo);

MAKE_COMPRESS_BENCHMARK(compressBase64, hello_world);
MAKE_COMPRESS_BENCHMARK(compressBase64, all_ascii);
MAKE_COMPRESS_BENCHMARK(compressBase64, temp_json);
MAKE_COMPRESS_BENCHMARK(compressBase64, temp_json_float);
MAKE_COMPRESS_BENCHMARK(compressBase64, lorem_ipsum);
MAKE_COMPRESS_BENCHMARK(compressBase64, pi);
MAKE_COMPRESS_BENCHMARK(compressBase64, repeated);
MAKE_COMPRESS_BENCHMARK(compressBase64, tattoo);

MAKE_COMPRESS_BENCHMARK(compressEncodedURI, hello_world);
MAKE_COMPRESS_BENCHMARK(compressEncodedURI, all_ascii);
MAKE_COMPRESS_BENCHMARK(compressEncodedURI, temp_json);
MAKE_COMPRESS_BENCHMARK(compressEncodedURI, temp_json_float);
MAKE_COMPRESS_BENCHMARK(compressEncodedURI, lorem_ipsum);
MAKE_COMPRESS_BENCHMARK(compressEncodedURI, pi);
MAKE_COMPRESS_BENCHMARK(compressEncodedURI, repeated);
MAKE_COMPRESS_BENCHMARK(compressEncodedURI, tattoo);

MAKE_COMPRESS_BENCHMARK(compressUint8Array, hello_world);
MAKE_COMPRESS_BENCHMARK(compressUint8Array, all_ascii);
MAKE_COMPRESS_BENCHMARK(compressUint8Array, temp_json);
MAKE_COMPRESS_BENCHMARK(compressUint8Array, temp_json_float);
MAKE_COMPRESS_BENCHMARK(compressUint8Array, lorem_ipsum);
MAKE_COMPRESS_BENCHMARK(compressUint8Array, pi);
MAKE_COMPRESS_BENCHMARK(compressUint8Array, repeated);
MAKE_COMPRESS_BENCHMARK(compressUint8Array, tattoo);

/*
 * ---------------------------------------------------------------------------------------------------
 * -- Decompress benchmarks
*/

#define MAKE_DECOMPRESS_BENCHMARK(compressfunc, decompressfunc, inputs)               \
  static void BM_decompress_##decompressfunc##_##inputs(benchmark::State& state) {    \
    auto compressed = pxd::lz_string::compressfunc(pxd::lz_string::to_utf16(inputs)); \
                                                                                      \
    for(auto _ : state) {                                                             \
      auto decompressed = pxd::lz_string::decompressfunc(compressed);                 \
    }                                                                                 \
  }                                                                                   \
  BENCHMARK(BM_decompress_##decompressfunc##_##inputs)->Iterations(NUM_ITER);

MAKE_DECOMPRESS_BENCHMARK(compress, decompress, hello_world);
MAKE_DECOMPRESS_BENCHMARK(compress, decompress, all_ascii);
MAKE_DECOMPRESS_BENCHMARK(compress, decompress, temp_json);
MAKE_DECOMPRESS_BENCHMARK(compress, decompress, temp_json_float);
MAKE_DECOMPRESS_BENCHMARK(compress, decompress, lorem_ipsum);
MAKE_DECOMPRESS_BENCHMARK(compress, decompress, pi);
MAKE_DECOMPRESS_BENCHMARK(compress, decompress, repeated);
MAKE_DECOMPRESS_BENCHMARK(compress, decompress, tattoo);

MAKE_DECOMPRESS_BENCHMARK(compressUTF16, decompressUTF16, hello_world);
MAKE_DECOMPRESS_BENCHMARK(compressUTF16, decompressUTF16, all_ascii);
MAKE_DECOMPRESS_BENCHMARK(compressUTF16, decompressUTF16, temp_json);
MAKE_DECOMPRESS_BENCHMARK(compressUTF16, decompressUTF16, temp_json_float);
MAKE_DECOMPRESS_BENCHMARK(compressUTF16, decompressUTF16, lorem_ipsum);
MAKE_DECOMPRESS_BENCHMARK(compressUTF16, decompressUTF16, pi);
MAKE_DECOMPRESS_BENCHMARK(compressUTF16, decompressUTF16, repeated);
MAKE_DECOMPRESS_BENCHMARK(compressUTF16, decompressUTF16, tattoo);

MAKE_DECOMPRESS_BENCHMARK(compressBase64, decompressBase64, hello_world);
MAKE_DECOMPRESS_BENCHMARK(compressBase64, decompressBase64, all_ascii);
MAKE_DECOMPRESS_BENCHMARK(compressBase64, decompressBase64, temp_json);
MAKE_DECOMPRESS_BENCHMARK(compressBase64, decompressBase64, temp_json_float);
MAKE_DECOMPRESS_BENCHMARK(compressBase64, decompressBase64, lorem_ipsum);
MAKE_DECOMPRESS_BENCHMARK(compressBase64, decompressBase64, pi);
MAKE_DECOMPRESS_BENCHMARK(compressBase64, decompressBase64, repeated);
MAKE_DECOMPRESS_BENCHMARK(compressBase64, decompressBase64, tattoo);

MAKE_DECOMPRESS_BENCHMARK(compressEncodedURI, decompressEncodedURI, hello_world);
MAKE_DECOMPRESS_BENCHMARK(compressEncodedURI, decompressEncodedURI, all_ascii);
MAKE_DECOMPRESS_BENCHMARK(compressEncodedURI, decompressEncodedURI, temp_json);
MAKE_DECOMPRESS_BENCHMARK(compressEncodedURI, decompressEncodedURI, temp_json_float);
MAKE_DECOMPRESS_BENCHMARK(compressEncodedURI, decompressEncodedURI, lorem_ipsum);
MAKE_DECOMPRESS_BENCHMARK(compressEncodedURI, decompressEncodedURI, pi);
MAKE_DECOMPRESS_BENCHMARK(compressEncodedURI, decompressEncodedURI, repeated);
MAKE_DECOMPRESS_BENCHMARK(compressEncodedURI, decompressEncodedURI, tattoo);

MAKE_DECOMPRESS_BENCHMARK(compressUint8Array, decompressUint8Array, hello_world);
MAKE_DECOMPRESS_BENCHMARK(compressUint8Array, decompressUint8Array, all_ascii);
MAKE_DECOMPRESS_BENCHMARK(compressUint8Array, decompressUint8Array, temp_json);
MAKE_DECOMPRESS_BENCHMARK(compressUint8Array, decompressUint8Array, temp_json_float);
MAKE_DECOMPRESS_BENCHMARK(compressUint8Array, decompressUint8Array, lorem_ipsum);
MAKE_DECOMPRESS_BENCHMARK(compressUint8Array, decompressUint8Array, pi);
MAKE_DECOMPRESS_BENCHMARK(compressUint8Array, decompressUint8Array, repeated);
MAKE_DECOMPRESS_BENCHMARK(compressUint8Array, decompressUint8Array, tattoo);

BENCHMARK_MAIN();
