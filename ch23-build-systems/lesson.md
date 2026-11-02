## Ch23 · Build Systems

The programs in this course have each been one executable built from one file, and that's the simplest case for CMake. Larger projects are made of several libraries and programs, with settings that depend on the build. This chapter covers library targets, the settings that connect targets, and options that change how code is built.

The steps are:

* [Library targets](#goto/01-library-target): building shared code once as a library, and linking it into a program.
* [Options](#goto/02-options): a CMake option, a compile definition, and a preprocessor check that together change a build.
* [Summary](#goto/03-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The examples and explanations are new. They use the same header-and-source split as the headers chapter, and the C versions use the CMake commands the C++ course uses.*
