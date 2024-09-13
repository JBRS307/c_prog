cmake_minimum_required(VERSION 3.22)

project(Strings)

add_compile_options(-Wall -g)


add_executable(palindrome palindrome.c)
add_executable(firstrep first_repetition.c)
add_executable(countchars character_counter.c)
add_executable(countvc count_vowels_consonants.c)

set_target_properties(
    palindrome firstrep countchars countvc
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)