cmake_minimum_required(VERSION 3.28)

PROJECT(TemplateCPP20 VERSION 1.0.0 LANGUAGES CXX)

# path targets
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# make dynamic cfs
add_subdirectory(configured)

# make app
add_subdirectory(src)

# clean
add_custom_target (clean-all COMMAND rm -rf ${CMAKE_BINARY_DIR}/*
                             COMMAND rm -rf ${CMAKE_BINARY_DIR}/.cmake
                             COMMAND rm -rf ${CMAKE_BINARY_DIR}/.ninja_*
                             COMMAND rm -rf ${CMAKE_SOURCE_DIR}/bin/*)
