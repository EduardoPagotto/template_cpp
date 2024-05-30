# Template CPP
Template files to setup the environment in c++ development

## Features
- VSCode setup<p>
   import profile: "./deps/clang_base.code-profile"
- CLang-format
- toolchain Clang++ (c++20)
- CMake
- Font JetBrain <p>
   ref: https://www.jetbrains.com/pt-br/lp/mono/

## To Build:

Execute commands:
```bash
mkdir build
cd build
cmake ../ -DCMAKE_TOOLCHAIN_FILE=./toolchain/clang.cmake
make
#cmake -B build -DCMAKE_TOOLCHAIN_FILE=./toolchain/clang.cmake
```
