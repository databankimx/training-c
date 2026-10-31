## Homework: Required file

Write a program that reads a file the program needs. If the file can't be opened, the reading function reports it through its return value, and `main` reports the problem.

The program should:

* define `print_file`, which takes a file name as a `const char *`, opens the file, and returns -1 when it can't
* print each line of the file when it opens, using `fgets`
* in `main`, call `print_file` on `data/settings.txt`, and print the file's lines
* when the call returns -1, print `could not open data/settings.txt`, and return a non-zero value from `main`

The file `data/settings.txt` is already in the step's `data` folder.

### What to check

Run the program as it is. The two lines of the settings file should appear, and no error should be reported.

Then change the file name to `data/missing.txt`, and run again. The output should be `could not open data/missing.txt`, and the program should return a non-zero value.

### Extensions

* Check for an empty file name before opening it, and return a different code for it. Decide whether an empty name is a mistake in the program, or a problem with the data. That decides which code is right.
* Call `print_file` for two files, one after the other, so that a failure in the first doesn't stop the second. Think about where the check on each return value has to go.

---

*This exercise is not from the book. It practices the ideas in Chapter 9, and it uses the file reading from Chapter 8.*
