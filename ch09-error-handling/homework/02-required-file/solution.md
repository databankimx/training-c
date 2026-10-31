## Walkthrough: Required file

`print_file` has one job: open the file, print it, and report success or failure. It returns -1 as soon as `fopen` fails, and before it does any printing. Because it returns before opening anything, there's no file to close on that path.

`main` checks the return value, and it's the only place that decides what a failure means to the user. The message is printed there, so the function that reads the file doesn't need to know how the program talks to its user.

`fgets` keeps the newline, so `printf("%s", line)` prints each line exactly as it appears in the file, with no extra blank lines.

The extension about two files shows why the check belongs after each call. A check at the end of a long sequence would only see the last result, and the first failure would be hidden.
