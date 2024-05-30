# Template CPP
Environment to C++20 development template

## Features
- VSCode profile: [clang_base](./deps/clang_base.code-profile)
- VSCode Font: [JetBrains](https://www.jetbrains.com/pt-br/lp/mono/)
- Clang-format: [format](.clang-format)
- Toolchain cmake:[clang.cmake](./toolchain/clang.cmake)

## To Build and compile:

Execute commands:
```sh
mkdir build
cd build
cmake ../ -DCMAKE_TOOLCHAIN_FILE=./toolchain/clang.cmake
make
# or
# cmake -B build -DCMAKE_TOOLCHAIN_FILE=./toolchain/clang.cmake
```
