cmake_minimum_required(VERSION 3.5.0)
project(lz_string VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_BUILD_TYPE Debug)

set(PXD_TEST_PROJECT_NAME ${PROJECT_NAME}_test)

set(CXX_VERSION 20)

set(CMAKE_CXX_STANDARD ${CXX_VERSION})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${CXX_VERSION}")
endif()

if(NOT WIN32)
    set(IWYU_ARGS include-what-you-use -w -Xiwyu --verbose=7)
    add_compile_definitions(CMAKE_CXX_INCLUDE_WHAT_YOU_USE=${IWYU_ARGS})
endif(NOT WIN32)

set(PXD_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party)
set(PXD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PXD_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(PXD_HEADER_FILES
    ${PXD_INCLUDE_DIR}/lz_string.hpp
)

set(PXD_SOURCE_FILES
    ${PXD_SOURCE_DIR}/lz_string.cpp
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

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(PXD_TEST_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
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
        ${COMMON_STD_HEADERS}
        ${PXD_HEADER_FILES}
    )

endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
        