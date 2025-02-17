cmake_minimum_required(VERSION 3.10.0)
project(lz_string VERSION 0.1.0 LANGUAGES C CXX)

if(NOT MSVC)
    set(CMAKE_BUILD_TYPE "Release")
endif(NOT MSVC)

option(PXD_BUILD_TEST "Build test executable" OFF)
option(PXD_BUILD_BENCHMARK "Build benchmark executable" OFF)

set(CXX_VERSION 20)

set(CMAKE_CXX_STANDARD ${CXX_VERSION})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${CXX_VERSION}")
endif()

if(NOT WIN32)
    set(IWYU_ARGS "include-what-you-use -w -Xiwyu --verbose=7")
    add_compile_definitions(CMAKE_CXX_INCLUDE_WHAT_YOU_USE=${IWYU_ARGS})
endif(NOT WIN32)

if(${CMAKE_BUILD_TYPE} MATCHES "Release")

  message(STATUS "Optimizations are opened for ${PROJECT_NAME}")

  include(CheckIPOSupported)
  check_ipo_supported(RESULT is_supported OUTPUT error)

  if(is_supported)
    message(STATUS "Opening LTO")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif(is_supported)

  if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Adding -O3 -march=native flags")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")
  endif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")

endif(${CMAKE_BUILD_TYPE} MATCHES "Release")

set(PXD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PXD_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(PXD_HEADER_FILES
    ${PXD_INCLUDE_DIR}/lz_string.hpp
)

set(PXD_SOURCE_FILES
    ${PXD_SOURCE_DIR}/lz_string.cpp

    ${PXD_HEADER_FILES}
)

include_directories(
    ${PXD_INCLUDE_DIR}
)

set(COMMON_STD_HEADERS
    <string>
    <algorithm>
    <cmath>
    <functional>
    <numeric>
    <string_view>
    <unordered_map>
    <unordered_set>
    <vector>
    <cstdint>
)

set(LIBS_TO_LINK
)

add_library(${PROJECT_NAME} ${PXD_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${LIBS_TO_LINK})

target_precompile_headers(
    ${PROJECT_NAME} PRIVATE
    ${COMMON_STD_HEADERS}
    ${PXD_HEADER_FILES}
)

# ------------------------------------------------------------------------------
# -- Test Executable

set(PXD_TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_src)

if(PXD_BUILD_TEST)
    set(PXD_TEST_PROJECT_NAME ${PROJECT_NAME}_test)

    set(PXD_TEST_SOURCE_FILES
        ${PXD_TEST_SOURCE_DIR}/utilities.hpp
        ${PXD_TEST_SOURCE_DIR}/utilities.cpp

        ${PXD_TEST_SOURCE_DIR}/compress_tests.cpp
        ${PXD_TEST_SOURCE_DIR}/compress_utf16_tests.cpp
        ${PXD_TEST_SOURCE_DIR}/compress_base64_tests.cpp
        ${PXD_TEST_SOURCE_DIR}/compress_uri_tests.cpp
        ${PXD_TEST_SOURCE_DIR}/compress_uint8arr_tests.cpp

        ${PXD_TEST_SOURCE_DIR}/decompress_tests.cpp
        ${PXD_TEST_SOURCE_DIR}/decompress_utf16_tests.cpp
        ${PXD_TEST_SOURCE_DIR}/decompress_base64_tests.cpp
        ${PXD_TEST_SOURCE_DIR}/decompress_uri_tests.cpp
        ${PXD_TEST_SOURCE_DIR}/decompress_uint8arr_tests.cpp

        ${PXD_SOURCE_FILES}
    )

    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest/
        GIT_TAG main
    )

    if(WIN32)
        # For Windows: Prevent overriding the parent project's compiler/linker settings
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif(WIN32)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(${PXD_TEST_PROJECT_NAME} ${PXD_TEST_SOURCE_FILES})

    target_link_libraries(${PXD_TEST_PROJECT_NAME} ${LIBS_TO_LINK} GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(${PXD_TEST_PROJECT_NAME})

    target_precompile_headers(
        ${PXD_TEST_PROJECT_NAME} PRIVATE
        ${PXD_TEST_SOURCE_DIR}/utilities.hpp
        ${COMMON_STD_HEADERS}
        ${PXD_HEADER_FILES}
    )

endif()
unset(PXD_BUILD_TEST CACHE)

if(PXD_BUILD_BENCHMARK)
    set(PXD_BENCHMARK_PROJECT_NAME ${PROJECT_NAME}_benchmark)
    set(PXD_BENCHMARK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/benchmark_src)

    set(PXD_BENCHMARK_SOURCE_FILES
        ${PXD_BENCHMARK_SOURCE_DIR}/benchmark.cpp

        ${PXD_TEST_SOURCE_DIR}/utilities.hpp
        ${PXD_TEST_SOURCE_DIR}/utilities.cpp

        ${PXD_SOURCE_FILES}
    )

    set(BENCHMARK_ENABLE_TESTING OFF)

    include(FetchContent)
    FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark/
        GIT_TAG main
    )
    FetchContent_MakeAvailable(googlebenchmark)

    add_executable(${PXD_BENCHMARK_PROJECT_NAME} ${PXD_BENCHMARK_SOURCE_FILES})

    target_link_libraries(${PXD_BENCHMARK_PROJECT_NAME} ${LIBS_TO_LINK} benchmark::benchmark)

    target_precompile_headers(
        ${PXD_BENCHMARK_PROJECT_NAME} PRIVATE
        ${COMMON_STD_HEADERS}
        ${PXD_TEST_SOURCE_DIR}/utilities.hpp
        ${PXD_HEADER_FILES}
    )

endif()
unset(PXD_BUILD_BENCHMARK CACHE)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
