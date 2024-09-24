cmake_minimum_required(VERSION 3.22)

project(MySQL)

add_compile_options(-Wall -g -std=gnu17)
add_link_options(-lmysqlclient)