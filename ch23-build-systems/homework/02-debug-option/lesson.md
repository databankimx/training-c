## Homework: Debug option

Add an option that turns on extra output in a program. The option is off by default, so the normal output doesn't change, and it's turned on with a compile definition that the code checks with `#ifdef`.

The program should:

* declare `option(SHOW_STEPS "Print each step of the calculation" OFF)` in `CMakeLists.txt`
* when `SHOW_STEPS` is on, define `SHOW_STEPS_ON=1` for the program target, using `target_compile_definitions`
* in `main.c`, compute the sum of 1 through 4 with a loop, and print `Sum: 10`
* when `SHOW_STEPS_ON` is defined, also print one line for each number added, in the form `Adding 1: total 1`, with the running total after each addition

### What to check

With the option off, the output should be:

```
Sum: 10
```

To check the other behavior, change the default of `SHOW_STEPS` to ON in `CMakeLists.txt`, and press **Run**. You don't write `SHOW_STEPS_ON` yourself. When the option is ON, the `if(SHOW_STEPS)` block in `CMakeLists.txt` defines `SHOW_STEPS_ON` for the program, and the `#ifdef` in `main.c` then compiles the step lines. The output should then be:

```
Adding 1: total 1
Adding 2: total 3
Adding 3: total 6
Adding 4: total 10
Sum: 10
```

Change the default back to OFF before you finish, so the normal build stays quiet.

You can also turn the option on without editing the file. From a terminal in the step's folder, run `cmake -S . -B build -DSHOW_STEPS=ON`, then `cmake --build build`. That's the same setting as the default, applied for that build only.

### Extensions

* Explain why the option is set in `CMakeLists.txt` rather than in `main.c`, and what would happen to the `#ifdef` if the definition were missing.
* Add a second option that changes the sum to a product. Decide whether the two options can be on at the same time, and what the code should do if they are.

---

*This exercise is not from the book. It practices the ideas in Chapter 23.*
