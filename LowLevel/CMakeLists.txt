cmake_minimum_required(VERSION 3.22)

project(LowLevel)

add_compile_options(-Wall -g -std=gnu17)

add_executable(bintodec bin_to_dec.c)
add_executable(dectobin dec_to_bin.c)

set_target_properties(
    bintodec dectobin
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)