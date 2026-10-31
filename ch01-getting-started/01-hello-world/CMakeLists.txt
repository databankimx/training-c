# Hello world: a program with a single executable called program.
cmake_minimum_required(VERSION 3.25)
project(hello_world LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

# With the runner's Backtrace option on, add debug information.
if(LESSON_BACKTRACE)
    add_compile_options(-g)
endif()

# The runner runs the executable called program.
add_executable(program src/main.c)
