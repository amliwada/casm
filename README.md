# casm
Compile-time x86/x86-64 bytecode generator. You can use it like a inline assembler.

## Features

- Support for x86, x64, mmx, sse, sse2, sse3, ssse3, sse4.1, sse4.2
- Working with any C++17 compiler
- Support for Windows, Linux and macOS
- No dependencies
- Header-only

## Examples

#### CMakeLists.txt

```CMake
add_executable(casm_example main.cpp)
set_target_properties(casm_example PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(casm GIT_REPOSITORY https://github.com/amliwada/casm.git GIT_TAG v1.0.6)
FetchContent_MakeAvailable(casm)

target_link_libraries(casm_example casm)
```

#### main.cpp

### Assembler

```C++
#include <casm.hpp>

int main()
{
  using namespace casm;

  int i = 0x14;

  assembler code
  {	
    push(rdx),
    mov(rdx, &i),
    add(dword [rdx], 0x21042005),
    pop(rdx)
  };

  auto bytecode = code.bytecode();

  return 0;
}
```

### Inline assembler

```C++
#include <casm.hpp>

#include <cassert>

int main()
{
  using namespace casm;

  int i = 0x14;

  f my_f
  {	
    push(rcx),
    mov(rcx, &i),

    push(rax),
    xor_(rax, rax),

    "loop"_l,

    inc(rax),
    sub(byte_ptr [rcx], 7),

    cmp(byte_ptr [rcx], 0),
    jnz("loop"_l),

    pop(rax),
    pop(rcx)
  };

  my_f();

  assert(i == 0);

  return 0;
}
```

### Single instructions

https://github.com/amliwada/casm/blob/dedad95cc4409cf560aec903fa297e4bda3c75e4/tests/main.cpp#L10115-L10119

### More Examples

More examples can be found in the [tests](./tests/) directory.

## Build

Copy and include source/casm.hpp
