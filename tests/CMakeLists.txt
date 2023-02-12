enable_language(ASM_NASM)
add_executable(casm_testing main.cpp instructions.asm)
set_target_properties(casm_testing PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
target_include_directories(casm_testing PRIVATE "${CMAKE_SOURCE_DIR}/include")

include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG release-1.11.0)
FetchContent_MakeAvailable(googletest)
target_link_libraries(casm_testing PRIVATE gtest_main)

add_test(NAME casm_test COMMAND "${CMAKE_BINARY_DIR}/bin/casm_testing")