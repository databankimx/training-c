# Include guards: a program built from two source files, battery.c and main.c.
cmake_minimum_required(VERSION 3.25)
project(include_guards LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

if(LESSON_BACKTRACE)
    add_compile_options(-g)
endif()

add_executable(program src/main.c src/battery.c)
