# Combining modules: a program built from main.c and three modules, each with its own header.
cmake_minimum_required(VERSION 3.25)
project(combining_modules LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

if(LESSON_BACKTRACE)
    add_compile_options(-g)
endif()

add_executable(program src/main.c src/car.c src/battery.c src/electric_car.c)
