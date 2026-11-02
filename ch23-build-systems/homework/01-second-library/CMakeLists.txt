# Second library: a program linked with a static library called mathutil.
cmake_minimum_required(VERSION 3.25)
project(second_library LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

add_library(mathutil STATIC src/mathutil.c)
target_include_directories(mathutil PUBLIC src)

add_executable(program src/main.c)
target_link_libraries(program PRIVATE mathutil)
