cmake_minimum_required(VERSION 3.22)

project(MySQL)

set(MYSQL_INCLUDE_DIR /usr/include/mysql)
set(MYSQL_LINK_DIR /usr/lib/mysql)

add_compile_options(-Wall -g -std=gnu17)
include_directories(${MYSQL_INCLUDE_DIR})
link_directories(${MYSQL_LINK_DIR})
link_libraries(-lmysqlclient)

add_executable(display display_all_tables.c)
add_executable(insert insert_into_table.c)
add_executable(search search.c)
add_executable(update update.c)

set_target_properties(
    display insert search update
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)