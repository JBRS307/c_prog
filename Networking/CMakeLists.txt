cmake_minimum_required(VERSION 3.22)

project(Networking)

add_compile_options(-Wall -g -std=gnu17)

add_executable(single single_process_read_write.c)

set_target_properties(
    single
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)