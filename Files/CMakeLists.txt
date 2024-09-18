cmake_minimum_required(VERSION 3.22)

project(Files)

add_compile_options(-Wall -g -std=gnu17)

add_executable(readconv read_and_convert.c)

set_target_properties(
    readconv
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
