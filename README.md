# casm
Compile-time x86/x86-64 bytecode generator. You can use it like a inline assembler.

## Features

- Support for x86, x64, mmx, sse, sse2, sse3, ssse3, sse4.1, sse4.2
- Working with any C++17 compiler
- Support for Windows, Linux and macOS
- No dependencies
- Header-only

## Examples

### Inline assembler

https://github.com/amliwada/casm/blob/5b5e3ecec0d5c590798a5cdfe54430cf1ecba140/tests/main.cpp#L10086-L10110

### Single instructions

https://github.com/amliwada/casm/blob/b67b6f4d4abaa58c66b493d945906db45f7580bb/tests/main.cpp#L10115-L10119

### More Examples

More examples can be found in the [tests](./tests/) directory.

## Build

Copy and include source/casm.hpp
