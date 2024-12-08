# lz-string

C++20 implemantation of [lz-string](https://github.com/pieroxy/lz-string)

## Features

- Includes all compresses and decompresses
- No dependencies (tests require GoogleTest)

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

- Last updated date (dd-MM-yyyy): 08-12-2024

|       Function       | HelloWorld | AllASCII | JSON | JSONFloat |
| :------------------: | :--------: | :------: | :--: | :-------: |
|       Compress       |     ✔     |    ✔    |  ✔  |     𐄂     |
|    CompressUTF16     |     ✔     |    ✔    |  ✔  |     𐄂     |
|    CompressBase64    |     ✔     |    ✔    |  ✔  |     𐄂     |
|     CompressURI      |     ✔     |    ✔    |  ✔  |     𐄂     |
|  CompressUint8Array  |     ✔     |    ✔    |  ✔  |     𐄂     |
|      Decompress      |     ✔     |    ✔    |  ✔  |    ✔     |
|   DecompressUTF16    |     ✔     |    ✔    |  ✔  |    ✔     |
|   DecompressBase64   |     ✔     |    ✔    |  ✔  |    ✔     |
|    DecompressURI     |     ✔     |    ✔    |  ✔  |    ✔     |
| DecompressUint8Array |     ✔     |    ✔    |  ✔  |    ✔     |
