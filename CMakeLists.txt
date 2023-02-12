cmake_minimum_required(VERSION 3.12)

project(casm VERSION 1.0 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CASM_BUILD_TESTS ON CACHE BOOL "Build the tests (Requires https://github.com/google/googletest)" FORCE)

if (CASM_BUILD_TESTS)
    include(CTest)

    add_subdirectory(tests)
endif()