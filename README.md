# lz-string

C++20 implemantation of [lz-string](https://github.com/pieroxy/lz-string)

## Features
- Includes all compresses and decompresses (except ```UInt8Array``` right now)
- No dependencies (tests require GoogleTest)

## Tests
- Current tests are:

| Test Name  | Description                                         |
| :--------: | :-------------------------------------------------- |
| HelloWorld | Classic hello world                                 |
|  AllASCII  | Including all the ASCII characters                  |
|    JSON    | Temp json including all data types except float     |
| JSONFloat  | Temp json file including floats, objects and arrays |

- Can run the tests with ```run_tests``` script files.

### Test Results

- Last updated date (dd-MM-yyyy): 06-12-2024

|    Function    | HelloWorld | AllASCII | JSON  | JSONFloat |
| :------------: | :--------: | :------: | :---: | :-------: |
|    Compress    |     ✅      |    ❎     |   ✅   |     ❎     |
| CompressUTF16  |     ✅      |    ❎     |   ✅   |     ❎     |
| CompressBase64 |     ✅      |    ❎     |   ✅   |     ❎     |
|  CompressURI   |     ✅      |    ❎     |   ✅   |     ❎     |

- ✅ : Passed 
- ❎ : Failed   
