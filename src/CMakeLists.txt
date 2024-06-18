PROJECT(template_cpp VERSION 1.0.0 LANGUAGES CXX)

# other conf's in ./toolchain/clang.cmake
set(CMAKE_CXX_FLAGS "-std=c++20 -ftest-coverage -fprofile-arcs -fstandalone-debug ${CMAKE_CXX_FLAGS}")

message(STATUS "*********************************************")
message(STATUS "CMAKE_FIND_ROOT_PATH: ${CMAKE_FIND_ROOT_PATH}")
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "*********************************************")

set(include_dir ${CMAKE_SOURCE_DIR}/include
                ${CMAKE_BINARY_DIR}/configured_files/include)

set(source_dir ${CMAKE_SOURCE_DIR}/src)

set(libs_def -lpthread)

add_executable (${PROJECT_NAME} ${source_dir}/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${include_dir})                                         
target_link_libraries(${PROJECT_NAME} ${libs_def})

# # Create aux files
# add_custom_command(TARGET ${PROJECT_NAME}
#         POST_BUILD
#         COMMAND ${CMAKE_SIZEUTIL} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} # Print PROJECT_NAME size
#         COMMAND ${CMAKE_OBJDUMP} -D ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} > ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${PROJECT_NAME}.list
#         COMMAND ${CMAKE_OBJCOPY} -O ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex
#         COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${PROJECT_NAME}.bin
#         COMMAND ${CMAKE_OBJDUMP} -d ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} -l > ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${PROJECT_NAME}.s
# )

# INSTALL(FILES ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME} DESTINATION bin)
