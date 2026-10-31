## Introduce yourself

The example has one `printf` for each line. Each call ends in `\n`, so every line starts on its own. The `'` in `I'm` needs no special handling inside a string, since only the double quotation mark ends a string.

Each `printf` takes the whole line, and the program does nothing else. That's why the output is exactly the three lines, with `Finished with exit code 0` after them.

The extension asks you to print the lines with one `printf`. That works, with `\n` in the middle of the text, but the single call is harder to change: adding a line means editing a long string in the middle of the call, where a new `printf` would be a line of its own.
