cmake_minimum_required(VERSION 3.22)

project(Pointers)

add_compile_options(-Wall -g -std=gnu17)

add_executable(strrev reverse_string.c)

set_target_properties(
    strrev
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)