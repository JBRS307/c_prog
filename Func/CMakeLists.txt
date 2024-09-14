cmake_minimum_required(VERSION 3.22)

project(Func)

add_compile_options(-Wall -g)

add_executable(armstrong check_armstrong_number.c)
add_executable(gcd recursive_gcd.c)

set_target_properties(
    armstrong gcd
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(
    armstrong
    PRIVATE -lm
)