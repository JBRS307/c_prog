cmake_minimum_required(VERSION 3.22)

project(Arrays)

add_compile_options(-Wall)

add_executable(matmul matrix_multiplication.c)

set_target_properties(
    matmul
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)