# Word tally: a homework program built from main.c and hash_table.c.
cmake_minimum_required(VERSION 3.25)
project(word_tally LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(program src/main.c src/hash_table.c)
