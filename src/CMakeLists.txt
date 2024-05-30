set(include_dir ${CMAKE_SOURCE_DIR}/include)
set(source_dir ${CMAKE_SOURCE_DIR}/src)
set(libs_def -lpthread)

add_executable (simples ${source_dir}/main.cpp)

target_include_directories(simples PRIVATE ${include_dir})
target_link_libraries(simples ${libs_def})

INSTALL(FILES ${Simples_BINARY_DIR}/simples DESTINATION bin)
