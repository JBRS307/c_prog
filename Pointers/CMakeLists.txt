cmake_minimum_required(VERSION 3.22)

project(Pointers)

add_compile_options(-Wall -g -std=gnu17)

add_executable(strrev reverse_string.c)
add_executable(findmax find_max.c)
add_executable(sortlist sort_one_way_list.c)
add_executable(matt matrix_transpose.c)

set_target_properties(
    strrev findmax sortlist matt
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)