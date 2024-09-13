cmake_minimum_required(VERSION 3.22)

project(Strings)

add_compile_options(-Wall -g)

add_executable(palindrome palindrome.c)

set_target_properties(
    palindrome
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)