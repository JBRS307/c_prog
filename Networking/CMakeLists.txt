cmake_minimum_required(VERSION 3.22)

project(Networking)

add_compile_options(-Wall -g -std=gnu17)

add_executable(single single_process_read_write.c)
add_executable(childparent child_parent_pipe.c)
add_executable(fiforead fifo/fiforead.c)
add_executable(fifowrite fifo/fifowrite.c)

add_custom_target(fifo)
add_dependencies(fifo fiforead fifowrite)

set_target_properties(
    single childparent fiforead fifowrite
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)