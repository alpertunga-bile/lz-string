# lz-string

![build_badge](https://github.com/alpertunga-bile/lz-string/actions/workflows/build.yml/badge.svg) ![test_badge](https://github.com/alpertunga-bile/lz-string/actions/workflows/test.yml/badge.svg)

C++20 implementation of [lz-string](https://github.com/pieroxy/lz-string)

- [lz-string](#lz-string)
  - [Features](#features)
  - [Tests](#tests)
    - [Test Results](#test-results)
  - [Benchmark](#benchmark)

## Features

- Includes all compress and decompress functions
- No dependencies (tests require GoogleTest and benchmark require Google Benchmark. They are installed automatically.)

## Tests

- Current tests are:

|  Test Name  | Description                                         |
| :---------: | :-------------------------------------------------- |
| HelloWorld  | Classic hello world                                 |
|  AllASCII   | Including all the ASCII characters                  |
|    JSON     | Temp json including all data types except float     |
|  JSONFloat  | Temp json file including floats, objects and arrays |
|     PI      | PI number's digits                                  |
| Lorem Ipsum | Default lorem ipsum text                            |
|  Repeated   | Including repeated pattern                          |
|   Tattoo    | Classic text paragraph to test                      |

- Can run the tests with `run_tests` script files.

### Test Results

- Last updated date (dd-MM-yyyy): 13-12-2024

|       Function       | HelloWorld | AllASCII | JSON | JSONFloat | PI  | Lorem Ipsum | Repeated | Tattoo |
| :------------------: | :--------: | :------: | :--: | :-------: | :-: | :---------: | :------: | :----- |
|       Compress       |     ✔     |    ✔    |  ✔  |    ✔     | ✔  |     ✔      |    ✔    | ✔     |
|    CompressUTF16     |     ✔     |    ✔    |  ✔  |    ✔     | ✔  |     ✔      |    ✔    | ✔     |
|    CompressBase64    |     ✔     |    ✔    |  ✔  |    ✔     | ✔  |     ✔      |    ✔    | ✔     |
|     CompressURI      |     ✔     |    ✔    |  ✔  |    ✔     | ✔  |     ✔      |    ✔    | ✔     |
|  CompressUint8Array  |     ✔     |    ✔    |  ✔  |    ✔     | ✔  |     ✔      |    ✔    | ✔     |
|      Decompress      |     ✔     |    ✔    |  ✔  |    ✔     | ✔  |     ✔      |    ✔    | ✔     |
|   DecompressUTF16    |     ✔     |    ✔    |  ✔  |    ✔     | ✔  |     ✔      |    ✔    | ✔     |
|   DecompressBase64   |     ✔     |    ✔    |  ✔  |    ✔     | ✔  |     ✔      |    ✔    | ✔     |
|    DecompressURI     |     ✔     |    ✔    |  ✔  |    ✔     | ✔  |     ✔      |    ✔    | ✔     |
| DecompressUint8Array |     ✔     |    ✔    |  ✔  |    ✔     | ✔  |     ✔      |    ✔    | ✔     |

## Benchmark

<pre>
Running ./lz_string_benchmark
Run on (6 X 4100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 0.83, 1.11, 1.24
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
---------------------------------------------------------------------------------------------------------------
Benchmark                                                                     Time             CPU   Iterations
---------------------------------------------------------------------------------------------------------------
BM_compress_hello_world/iterations:100000                                  4.18 ns         4.14 ns       100000
BM_compress_all_ascii/iterations:100000                                    4.12 ns         4.12 ns       100000
BM_compress_temp_json/iterations:100000                                    4.15 ns         4.13 ns       100000
BM_compress_temp_json_float/iterations:100000                              4.12 ns         4.12 ns       100000
BM_compress_lorem_ipsum/iterations:100000                                  4.12 ns         4.12 ns       100000
BM_compress_pi/iterations:100000                                           4.15 ns         4.13 ns       100000
BM_compress_repeated/iterations:100000                                     4.12 ns         4.12 ns       100000
BM_compress_tattoo/iterations:100000                                       4.46 ns         4.44 ns       100000
BM_compressUTF16_hello_world/iterations:100000                             5.79 ns         5.79 ns       100000
BM_compressUTF16_all_ascii/iterations:100000                               6.29 ns         6.27 ns       100000
BM_compressUTF16_temp_json/iterations:100000                               6.35 ns         6.32 ns       100000
BM_compressUTF16_temp_json_float/iterations:100000                         5.68 ns         5.68 ns       100000
BM_compressUTF16_lorem_ipsum/iterations:100000                             6.20 ns         6.17 ns       100000
BM_compressUTF16_pi/iterations:100000                                      5.42 ns         5.42 ns       100000
BM_compressUTF16_repeated/iterations:100000                                5.95 ns         5.93 ns       100000
BM_compressUTF16_tattoo/iterations:100000                                  5.85 ns         5.84 ns       100000
BM_compressBase64_hello_world/iterations:100000                            4.95 ns         4.93 ns       100000
BM_compressBase64_all_ascii/iterations:100000                              4.02 ns         4.02 ns       100000
BM_compressBase64_temp_json/iterations:100000                              4.38 ns         4.36 ns       100000
BM_compressBase64_temp_json_float/iterations:100000                        4.09 ns         4.09 ns       100000
BM_compressBase64_lorem_ipsum/iterations:100000                            4.57 ns         4.55 ns       100000
BM_compressBase64_pi/iterations:100000                                     4.48 ns         4.49 ns       100000
BM_compressBase64_repeated/iterations:100000                               4.59 ns         4.57 ns       100000
BM_compressBase64_tattoo/iterations:100000                                 4.21 ns         4.21 ns       100000
BM_compressEncodedURI_hello_world/iterations:100000                        4.89 ns         4.88 ns       100000
BM_compressEncodedURI_all_ascii/iterations:100000                          4.74 ns         4.74 ns       100000
BM_compressEncodedURI_temp_json/iterations:100000                          5.61 ns         5.48 ns       100000
BM_compressEncodedURI_temp_json_float/iterations:100000                    5.31 ns         5.31 ns       100000
BM_compressEncodedURI_lorem_ipsum/iterations:100000                        5.01 ns         4.98 ns       100000
BM_compressEncodedURI_pi/iterations:100000                                 4.59 ns         4.59 ns       100000
BM_compressEncodedURI_repeated/iterations:100000                           5.54 ns         5.52 ns       100000
BM_compressEncodedURI_tattoo/iterations:100000                             5.09 ns         5.09 ns       100000
BM_compressUint8Array_hello_world/iterations:100000                        3.43 ns         3.42 ns       100000
BM_compressUint8Array_all_ascii/iterations:100000                          2.97 ns         2.97 ns       100000
BM_compressUint8Array_temp_json/iterations:100000                          3.20 ns         3.20 ns       100000
BM_compressUint8Array_temp_json_float/iterations:100000                    2.96 ns         2.96 ns       100000
BM_compressUint8Array_lorem_ipsum/iterations:100000                        3.71 ns         3.69 ns       100000
BM_compressUint8Array_pi/iterations:100000                                 2.76 ns         2.76 ns       100000
BM_compressUint8Array_repeated/iterations:100000                           3.30 ns         3.30 ns       100000
BM_compressUint8Array_tattoo/iterations:100000                             3.19 ns         3.17 ns       100000
BM_decompress_decompress_hello_world/iterations:100000                     4.52 ns         4.52 ns       100000
BM_decompress_decompress_all_ascii/iterations:100000                       5.20 ns         5.18 ns       100000
BM_decompress_decompress_temp_json/iterations:100000                       4.52 ns         4.52 ns       100000
BM_decompress_decompress_temp_json_float/iterations:100000                 4.55 ns         4.53 ns       100000
BM_decompress_decompress_lorem_ipsum/iterations:100000                     4.52 ns         4.52 ns       100000
BM_decompress_decompress_pi/iterations:100000                              4.85 ns         4.83 ns       100000
BM_decompress_decompress_repeated/iterations:100000                        4.52 ns         4.52 ns       100000
BM_decompress_decompress_tattoo/iterations:100000                          4.54 ns         4.53 ns       100000
BM_decompress_decompressUTF16_hello_world/iterations:100000                4.02 ns         4.02 ns       100000
BM_decompress_decompressUTF16_all_ascii/iterations:100000                  4.02 ns         4.02 ns       100000
BM_decompress_decompressUTF16_temp_json/iterations:100000                  4.32 ns         4.30 ns       100000
BM_decompress_decompressUTF16_temp_json_float/iterations:100000            4.02 ns         4.02 ns       100000
BM_decompress_decompressUTF16_lorem_ipsum/iterations:100000                4.05 ns         4.02 ns       100000
BM_decompress_decompressUTF16_pi/iterations:100000                         4.02 ns         4.02 ns       100000
BM_decompress_decompressUTF16_repeated/iterations:100000                   4.02 ns         4.02 ns       100000
BM_decompress_decompressUTF16_tattoo/iterations:100000                     4.33 ns         4.31 ns       100000
BM_decompress_decompressBase64_hello_world/iterations:100000               4.89 ns         4.89 ns       100000
BM_decompress_decompressBase64_all_ascii/iterations:100000                 4.92 ns         4.90 ns       100000
BM_decompress_decompressBase64_temp_json/iterations:100000                 4.89 ns         4.89 ns       100000
BM_decompress_decompressBase64_temp_json_float/iterations:100000           5.14 ns         5.13 ns       100000
BM_decompress_decompressBase64_lorem_ipsum/iterations:100000               4.89 ns         4.89 ns       100000
BM_decompress_decompressBase64_pi/iterations:100000                        4.87 ns         4.85 ns       100000
BM_decompress_decompressBase64_repeated/iterations:100000                  5.38 ns         5.38 ns       100000
BM_decompress_decompressBase64_tattoo/iterations:100000                    5.37 ns         5.35 ns       100000
BM_decompress_decompressEncodedURI_hello_world/iterations:100000           4.41 ns         4.41 ns       100000
BM_decompress_decompressEncodedURI_all_ascii/iterations:100000             4.59 ns         4.57 ns       100000
BM_decompress_decompressEncodedURI_temp_json/iterations:100000             4.27 ns         4.27 ns       100000
BM_decompress_decompressEncodedURI_temp_json_float/iterations:100000       4.38 ns         4.36 ns       100000
BM_decompress_decompressEncodedURI_lorem_ipsum/iterations:100000           4.45 ns         4.45 ns       100000
BM_decompress_decompressEncodedURI_pi/iterations:100000                    4.78 ns         4.76 ns       100000
BM_decompress_decompressEncodedURI_repeated/iterations:100000              4.47 ns         4.47 ns       100000
BM_decompress_decompressEncodedURI_tattoo/iterations:100000                4.81 ns         4.78 ns       100000
BM_decompress_decompressUint8Array_hello_world/iterations:100000           3.87 ns         3.87 ns       100000
BM_decompress_decompressUint8Array_all_ascii/iterations:100000             5.12 ns         5.10 ns       100000
BM_decompress_decompressUint8Array_temp_json/iterations:100000             4.13 ns         4.13 ns       100000
BM_decompress_decompressUint8Array_temp_json_float/iterations:100000       4.27 ns         4.27 ns       100000
BM_decompress_decompressUint8Array_lorem_ipsum/iterations:100000           4.08 ns         4.06 ns       100000
BM_decompress_decompressUint8Array_pi/iterations:100000                    4.80 ns         4.80 ns       100000
BM_decompress_decompressUint8Array_repeated/iterations:100000              4.24 ns         4.23 ns       100000
BM_decompress_decompressUint8Array_tattoo/iterations:100000                4.52 ns         4.52 ns       100000
</pre>
