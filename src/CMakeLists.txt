cmake_minimum_required(VERSION 3.22.1)

PROJECT(Simples)

add_executable (simples main.cpp)

INSTALL(FILES ${Simples_BINARY_DIR}/simples DESTINATION bin)
