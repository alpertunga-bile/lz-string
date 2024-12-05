cmake_minimum_required(VERSION 3.5.0)
project(lz_string VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include(setup.cmake)

set_cxx(20)
enable_iwyu()

set(PXD_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party)
set(PXD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PXD_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(PXD_HEADER_FILES
    ${PXD_INCLUDE_DIR}/lz_string.hpp
)

set(PXD_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${PXD_INCLUDE_DIR}/lz_string.cpp
)

include_directories(
    ${PXD_STL_INCLUDE_DIR}
)

set(COMMON_STD_HEADERS

)

set(LIBS_TO_LINK
)

add_executable(${PROJECT_NAME} ${PXD_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${LIBS_TO_LINK})

target_precompile_headers(
    ${PROJECT_NAME} PRIVATE
    ${COMMON_STD_HEADERS}
    ${PXD_HEADER_FILES}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
        