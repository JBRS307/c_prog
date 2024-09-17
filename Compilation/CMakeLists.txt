cmake_minimum_required(VERSION 3.22)

project(Compilation)

add_compile_options(-Wall -g)

add_executable(condcomp conditional_compilation.c)
add_executable(assert assertions_validation.c)
add_executable(assertnull null_assert.c)

set_target_properties(
    condcomp assert assertnull
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)