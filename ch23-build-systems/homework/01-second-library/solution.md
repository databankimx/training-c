## Walkthrough: Second library

The program and the library are separate targets, and the link line is what joins them. `target_link_libraries(program PRIVATE mathutil)` tells the linker to take `square` from the library, and `target_include_directories(mathutil PUBLIC src)` lets `main.c` find `mathutil.h`.

The extension about `cube` needs no change to `CMakeLists.txt`, because the library's source file is already listed. A new function in `mathutil.c`, declared in `mathutil.h`, is picked up when the library is rebuilt, and the program links the new version.

With the include folder changed to `PRIVATE`, the program can't find `mathutil.h`, since only the library's own build gets the folder. The compile fails with a missing header. That shows what PUBLIC is for: a header that a program includes must be visible to the program's build, and the library must say so.
