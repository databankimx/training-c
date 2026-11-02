## Introduce yourself

The example prints three lines, one `printf` for each. Each call ends in `\n`, so every line starts on its own. The name in the example, Ada, is a placeholder for your own, and the other two lines follow the wording the exercise asks for.

Each `printf` takes one whole line, and the program does nothing else. That's why the output is exactly three lines, with `Finished with exit code 0` after them.

The extension asks you to add `fflush(stdout);` after one line and not the others. The text looks the same in the Output pane, because the runner shows output in the order the program writes it. The flush matters when a program writes a prompt and then waits for an answer, as the user-input step showed.
