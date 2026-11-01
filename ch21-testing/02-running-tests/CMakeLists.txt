# Running tests with CTest: a program with a single executable called program, and one test registered with CTest.
cmake_minimum_required(VERSION 3.25)
project(running_tests LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(program src/main.c)

enable_testing()
add_test(NAME clamp_checks COMMAND program)
