cmake_minimum_required(VERSION 3.22)

project(Strings)

add_compile_options(-Wall -g)


add_executable(palindrome palindrome.c)
add_executable(firstrep first_repetition.c)
add_executable(countchars character_counter.c)
add_executable(countvc count_vowels_consonants.c)
add_executable(vowelsup vowels_to_upper.c)

set_target_properties(
    palindrome firstrep countchars countvc vowelsup
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)