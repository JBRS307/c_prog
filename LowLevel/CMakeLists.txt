cmake_minimum_required(VERSION 3.22)

project(LowLevel)

add_compile_options(-Wall -g -std=gnu17)

add_executable(bintodec bin_to_dec.c)
add_executable(dectobin dec_to_bin.c)
add_executable(dtbmask dec_to_bin_mask.c)
add_executable(mult inline_assemble_multiply.c)
add_executable(div inline_assemble_division.c)