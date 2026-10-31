## Walkthrough: Safe age

`read_age` does the work. It reads a line, converts it, and checks the conversion in two places. The end pointer from `strtol` shows whether any digits were read, and the character it stopped at must be the newline or the end of the string. That second test is what rejects `42abc`. Without it, `strtol` would return 42, and the program would accept the input.

The range check comes after the number is known to be valid, so it only looks at real numbers. The code stores the age through the pointer only when every check has passed, so `main` never sees a value from a rejected line.

`main` handles each code in turn. A valid age ends the loop with `break`. A bad answer prints its message and goes round again. The end-of-input code stops the program, because a read that finds no more input would otherwise repeat forever.

The C version doesn't need to clear the input after a bad answer, which the C++ version does. `fgets` reads the whole line, including the newline, so the next prompt starts with a fresh line.
