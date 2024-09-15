cmake_minimum_required(VERSION 3.22)

project(Func)

add_compile_options(-Wall -g)

add_executable(armstrong check_armstrong_number.c)
add_executable(gcd recursive_gcd.c)
add_executable(bintohex bin_to_hex.c)
add_executable(palindromenum palindrome_number.c)

set_target_properties(
    armstrong gcd bintohex palindromenum
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(
    armstrong
    PRIVATE -lm
)
target_link_libraries(
    bintohex
    PRIVATE -lm
)
target_link_libraries(
    palindromenum
    PRIVATE -lm
)