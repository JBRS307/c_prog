cmake_minimum_required(VERSION 3.22)

project(Concurrency)

add_compile_options(-Wall -g -std=gnu17)
add_link_options(-lpthread)

add_executable(single single_thread.c)
add_executable(multi multiple_threads.c)

set_target_properties(
    single multi
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)