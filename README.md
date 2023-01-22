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

```C++
#include "casm.hpp"

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

https://github.com/amliwada/casm/blob/06fd7b7d5d533f7529a7de5b3104395559f48a94/tests/main.cpp#L10115-L10119

### More Examples

More examples can be found in the [tests](./tests/) directory.

## Build

Copy and include source/casm.hpp
