# lesson-runner: the C lesson runner. This first stage builds the discovery code and its test tool.
cmake_minimum_required(VERSION 3.25)
project(lesson_runner LANGUAGES C RC)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

# cJSON comes from the course's vendored copy, fetched by resources\vendor\cjson\fetch-cjson.ps1.
set(CJSON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../resources/vendor/cjson")
add_library(cjson STATIC "${CJSON_DIR}/cJSON.c")
target_include_directories(cjson SYSTEM PUBLIC "${CJSON_DIR}")

# The lesson core: finds chapters, sections, steps, and homework, and builds and runs a step.
add_library(lesson_core STATIC host/discovery.c host/runner.c host/commands.c host/router.c)
target_include_directories(lesson_core PUBLIC host)
target_link_libraries(lesson_core PUBLIC cjson)

# The test tool, which prints the parts as JSON for a repository.
add_executable(lesson-list tools/lesson_list.c)
target_link_libraries(lesson-list PRIVATE lesson_core)

# The protocol test tool: sends commands to the router from the console, and prints the replies and events.
add_executable(router-test tools/router_test.c)
target_link_libraries(router-test PRIVATE lesson_core)

# The lesson runner itself: a GUI program that hosts the page and connects it to the router.
set(WEBVIEW2_SDK "${CMAKE_CURRENT_SOURCE_DIR}/../resources/vendor/webview2/sdk"
    CACHE PATH "The WebView2 SDK folder, which holds build/native/include and build/native/x64")
add_executable(lesson-runner WIN32 host/app.c host/app.rc)
target_include_directories(lesson-runner SYSTEM PRIVATE "${WEBVIEW2_SDK}/build/native/include")
target_link_libraries(lesson-runner PRIVATE lesson_core ole32 user32 gdi32)
target_link_options(lesson-runner PRIVATE -municode)
add_custom_command(TARGET lesson-runner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${WEBVIEW2_SDK}/build/native/x64/WebView2Loader.dll"
            $<TARGET_FILE_DIR:lesson-runner>)
