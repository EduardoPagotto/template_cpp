set(include_dir ${CMAKE_SOURCE_DIR}/include
                ${CMAKE_BINARY_DIR}/configured_files/include)
set(source_dir ${CMAKE_SOURCE_DIR}/src)
set(libs_def -lpthread)

add_executable (${EXECUTABLE_NAME} ${source_dir}/main.cpp)

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${include_dir})                                         
target_link_libraries(${EXECUTABLE_NAME} ${libs_def})

INSTALL(FILES ${${EXECUTABLE_NAME}_BINARY_DIR}/${EXECUTABLE_NAME} DESTINATION bin)
