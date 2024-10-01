cmake_minimum_required(VERSION 3.22)

project(Utils)

add_compile_options(-g -Wall -std=gnu17)

add_executable(atexit atexit.c)

target_link_libraries(atexit PRIVATE pthread)