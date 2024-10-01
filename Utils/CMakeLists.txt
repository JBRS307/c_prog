cmake_minimum_required(VERSION 3.22)

project(Utils)

add_compile_options(-g -Wall -std=gnu17)

add_executable(atexit atexit.c)
add_executable(clock clock.c)

target_link_libraries(atexit PRIVATE pthread)

target_compile_definitions(clock PRIVATE __BENCHMARK__)