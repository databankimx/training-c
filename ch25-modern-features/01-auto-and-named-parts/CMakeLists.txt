# auto and named parts: a program built as C23, so auto is available.
cmake_minimum_required(VERSION 3.25)
project(auto_and_named_parts LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(program src/main.c)
