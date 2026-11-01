## Walkthrough: Debug option

The option lives in `CMakeLists.txt` because the build decides whether the definition exists, and the code only reads it. The `#ifdef` in `main.c` is safe without the definition: the step lines are simply left out, and the normal output stays the same. Without the definition, the program still builds and prints only `Sum: 10`, which is the behavior the default must keep.

The running total is printed after each addition, inside the loop, so the lines show the total growing. The `#ifdef` sits inside the loop body, which lets the same loop serve both builds, with one extra line when the option is on.

For the product extension, both options can be on at once, since each one only adds a definition. The code must then decide which calculation to print, or print both in a fixed order, and the build should state that rule in its comments rather than leave it to chance.
