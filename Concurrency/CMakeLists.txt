cmake_minimum_required(VERSION 3.22)

project(Concurrency)

add_compile_options(-Wall -g -std=gnu17)

add_executable(single single_thread.c)

set_target_properties(
    single
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(single PRIVATE -lpthread)