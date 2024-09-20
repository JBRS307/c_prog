cmake_minimum_required(VERSION 3.22)

project(Files)

add_compile_options(-Wall -g -std=gnu17)

add_executable(readconv read_and_convert.c)
add_executable(revfile reverse_file.c)
add_executable(vowcnt count_vowels.c)
add_executable(wordrpl word_replace.c)
add_executable(caesar caesar_code.c)

set_target_properties(
    readconv revfile vowcnt wordrpl caesar
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
