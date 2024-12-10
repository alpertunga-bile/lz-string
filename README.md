# lz-string

![build_badge](https://github.com/alpertunga-bile/lz-string/actions/workflows/build.yml/badge.svg) ![test_badge](https://github.com/alpertunga-bile/lz-string/actions/workflows/test.yml/badge.svg)

C++20 implemantation of [lz-string](https://github.com/pieroxy/lz-string)

- [lz-string](#lz-string)
  - [Features](#features)
  - [Tests](#tests)
    - [Test Results](#test-results)
  - [Benchmark](#benchmark)

## Features

- Includes all compresses and decompresses
- No dependencies (tests require GoogleTest and benchmark require Google Benchmark. They are installed automatically.)

## Tests

- Current tests are:

| Test Name  | Description                                         |
| :--------: | :-------------------------------------------------- |
| HelloWorld | Classic hello world                                 |
|  AllASCII  | Including all the ASCII characters                  |
|    JSON    | Temp json including all data types except float     |
| JSONFloat  | Temp json file including floats, objects and arrays |

- Can run the tests with `run_tests` script files.

- Compress tests are following these steps:

  1. Get the encoded string with original script and convert it to Uint16Array
  2. Compress the input string with implementation and calculate uint16_t array
  3. Compare the results

- Decompress tests are following these steps:

  1. Compress the input string
  2. Decompress the compressed string
  3. Check equality of the input and the decompressed strings

### Test Results

- Last updated date (dd-MM-yyyy): 10-12-2024


|       Function       | HelloWorld | AllASCII | JSON  | JSONFloat |
| :------------------: | :--------: | :------: | :---: | :-------: |
|       Compress       |     ✔      |    ✔     |   ✔   |     ✔     |
|    CompressUTF16     |     ✔      |    ✔     |   ✔   |     ✔     |
|    CompressBase64    |     ✔      |    ✔     |   ✔   |     ✔     |
|     CompressURI      |     ✔      |    ✔     |   ✔   |     ✔     |
|  CompressUint8Array  |     ✔      |    ✔     |   ✔   |     ✔     |
|      Decompress      |     ✔      |    ✔     |   ✔   |     ✔     |
|   DecompressUTF16    |     ✔      |    ✔     |   ✔   |     ✔     |
|   DecompressBase64   |     ✔      |    ✔     |   ✔   |     ✔     |
|    DecompressURI     |     ✔      |    ✔     |   ✔   |     ✔     |
| DecompressUint8Array |     ✔      |    ✔     |   ✔   |     ✔     |

## Benchmark

- Number of iterations: 100.000
- The time values are averaged times and their units are nanoseconds(ns).

|       Function       | HelloWorld | AllASCII |  JSON  | JSONFloat |
| :------------------: | :--------: | :------: | :----: | :-------: |
|       Compress       |    7875    |   6150   |  6566  |   6023    |
|    CompressUTF16     |    7173    |   6055   |  5701  |   5997    |
|    CompressBase64    |    9419    |   8374   |  7581  |   8064    |
|     CompressURI      |    7999    |   8162   |  7370  |   7503    |
|  CompressUint8Array  |    7222    |   6787   |  6061  |   5283    |
|      Decompress      |    3962    |  29583   | 85067  |   41833   |
|   DecompressUTF16    |    3673    |  28939   | 79510  |   42326   |
|   DecompressBase64   |   12972    |  121859  | 220690 |  141283   |
|    DecompressURI     |   13499    |  127591  | 222502 |  142500   |
| DecompressUint8Array |    4838    |  43131   | 95870  |   52743   |
