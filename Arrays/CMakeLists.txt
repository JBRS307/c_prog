cmake_minimum_required(VERSION 3.22)

project(Arrays)

add_compile_options(-Wall)

add_executable(matmul matrix_multiplication.c)
add_executable(twocommon two_arrays_common.c)
add_executable(rmrepeat remove_repeats.c)

set_target_properties(
    matmul twocommon rmrepeat
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)