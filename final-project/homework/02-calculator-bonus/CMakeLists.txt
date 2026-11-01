# Bonus items: a calculator with ^, sqrt, and square and curly brackets, with selftest registered with CTest.
cmake_minimum_required(VERSION 3.25)
project(calculator_bonus LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(program src/main.c)
target_link_libraries(program PRIVATE m)

enable_testing()
add_test(NAME calculator_bonus_selftest COMMAND program selftest)
