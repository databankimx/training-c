# Options: a program linked with a static library called greeting, whose build is changed by the USE_LOUD option.
cmake_minimum_required(VERSION 3.25)
project(options LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

option(USE_LOUD "Print greetings in capitals" OFF)

add_library(greeting STATIC src/greeting.c)
target_include_directories(greeting PUBLIC src)

if(USE_LOUD)
    target_compile_definitions(greeting PRIVATE LOUD_GREETINGS=1)
endif()

add_executable(program src/main.c)
target_link_libraries(program PRIVATE greeting)
