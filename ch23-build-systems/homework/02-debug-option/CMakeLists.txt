# Debug option: a program whose extra output is turned on by the SHOW_STEPS option.
cmake_minimum_required(VERSION 3.25)
project(debug_option LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

option(SHOW_STEPS "Print each step of the calculation" OFF)

add_executable(program src/main.c)

if(SHOW_STEPS)
    target_compile_definitions(program PRIVATE SHOW_STEPS_ON=1)
endif()
