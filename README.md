# Template CPP
Environment C++20 development template

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

## Files tree description:
```
template_cpp
├── .clang-format               ; Clang ident source cfg 
├── CMakeLists.txt              ; cmake root file 
├── configured
│   ├── CMakeLists.txt          ; cmake dynamic cfgs
│   └── config_params.hpp.in    ; header dynamic data 
├── deps
│   └── clang_base.code-profile ; vscode extentions profile
├── .gitignore                  ; git ignore extentions
├── include
    ├── UniformBuffer.hpp       ; source header example 1
    └── WrapperBuffer.hpp       ; source header example 1
├── LICENSE                     ; Licence file
├── proj.code-workspace         ; vscode project cfgs
├── README.md                   ; Doc
├── src
│   ├── CMakeLists.txt          ; cmake main app
│   └── main.cpp                ; source main 
├── toolchain
│   └── clang.cmake             ; cmake toolchain
└── .vscode
    ├── c_cpp_properties.json   ; vscode cpp cfg
    └── cmake-kits.json         ; vscode cmake kit
```