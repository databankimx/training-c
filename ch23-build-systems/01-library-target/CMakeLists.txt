# Library target: a program built from main.c, linked with a static library called greeting.
cmake_minimum_required(VERSION 3.25)
project(library_target LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

add_library(greeting STATIC src/greeting.c)
target_include_directories(greeting PUBLIC src)

add_executable(program src/main.c)
target_link_libraries(program PRIVATE greeting)
