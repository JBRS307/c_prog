cmake_minimum_required(VERSION 3.22)

project(Compilation)

add_compile_options(-Wall -g -std=c17)

add_executable(condcomp conditional_compilation.c)
add_executable(assert assertions_validation.c)
add_executable(assertnull null_assert.c)
add_executable(assertcomp compile_time_assertions.c)
add_executable(str stringize_token_paste.c)

set_target_properties(
    condcomp assert assertnull assertcomp str
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)