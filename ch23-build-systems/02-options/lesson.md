## Options

A build often needs to behave in one of two ways: a debug build with extra output, or a release build without it, or a library that turns a feature on for some users and off for others. CMake lets the build choose with an option, a setting that's on or off, and a compile definition, a symbol the code can check.

The step's `CMakeLists.txt` declares the option, and applies it to the library:

```cmake
option(USE_LOUD "Print greetings in capitals" OFF)

if(USE_LOUD)
    target_compile_definitions(greeting PRIVATE LOUD_GREETINGS=1)
endif()
```

The `option` line creates a setting called `USE_LOUD`, with a description and a default of off. The `if` block runs only when the option is on, and then it defines `LOUD_GREETINGS` for the library's own source file.

The code checks the symbol with a preprocessor test, from `src/greeting.c`:

```c
#ifdef LOUD_GREETINGS
    for (char *p = out; *p != '\0'; p++) {
        *p = (char)toupper((unsigned char)*p);
    }
#endif
```

The `#ifdef` lines are handled before the compiler reads the code. When `LOUD_GREETINGS` is defined, the loop runs, and the text is converted to capitals. When it isn't, the loop is left out of the compiled file entirely.

The `toupper` call takes an `unsigned char` value, not a plain `char`. A negative `char` value would be undefined behavior in `toupper`, so the cast to `unsigned char` keeps the call within its defined range, and the result is cast back to `char` for storage.

Press **Run**. With the option off, the output is:

```
Hello, Scott!
Hello, Ada!
```

### Setting an option

The default is in `CMakeLists.txt`, but a builder can override it without editing the file. From a terminal in the step's folder:

```pwsh
cmake -S . -B build -DUSE_LOUD=ON
cmake --build build
```

The value is stored in `CMakeCache.txt` in the build folder, and it stays set until the cache is removed or the option is changed again. The runner reads the options the step declares and sets them from its own options panel, so an option can be switched on in the runner as well.

### Options and defaults

An option's default should be the behavior most users expect. A feature that changes the output, such as capitals, should usually be off unless someone asks for it. The description in the `option` line is what a builder sees in CMake's interface, so it should say what the option does.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `#ifdef LOUD_GREETINGS` check?
○ Whether the option is set in the CMake file.
→ Not quite. The check is in the code, and it sees only the symbol the build defines.
◉ Whether the symbol LOUD_GREETINGS was defined for this compilation.
→ Yes. The preprocessor decides which lines are compiled, before the compiler reads them.
○ Whether the user typed a name.
→ Not quite. The check has nothing to do with input.
````

````quiz
Where is an option's value kept when a builder sets it on the command line?
○ In the source file.
→ Not quite. Options are kept in the build cache, not in the source.
◉ In CMakeCache.txt in the build folder, until it's changed or the cache is removed.
→ Yes. The cache keeps each option's value between configuration runs.
○ In the operating system's environment variables.
→ Not quite. CMake stores option values in its own cache file.
````

---

### Try it in the runner

Change the default of `USE_LOUD` in `CMakeLists.txt` from OFF to ON, and predict the output before you press **Run**. It prints `HELLO, SCOTT!` and `HELLO, ADA!`, since the option now defines `LOUD_GREETINGS` and the capitalizing loop is compiled in.

---

An option lets one CMake file build the code in more than one way, and a preprocessor check selects the variant. The next step is the chapter summary, and then two homework exercises that add a library and an option of their own.
