cmake_minimum_required(VERSION 3.27.4)

PROJECT(CursosCPP20)

set(CMAKE_CXX_FLAGS "-std=c++20 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -fstandalone-debug")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(src)
