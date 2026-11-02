## Summary: Error handling

This chapter covered how a C program reports and handles failure, since C has no exceptions.

* **A failing function reports through its return value.** Return codes can be numbers, or named values with `#define` or `enum`.
* **Every call that can fail must be checked.** C ignores a return value without warning, so a forgotten check lets the failure pass silently.
* **`errno` holds the reason a library call failed.** It's set only on failure, so set it to 0 before the call, and read it straight after.
* **`strerror` turns an error number into text.** Compare `errno` with named constants such as `ENOENT` and `EACCES` to choose a message.
* **Check the return value first.** A failed call returns `NULL` or -1, and `errno` explains that failure.
* **Use `goto` to release resources.** Labels at the bottom of a function close what's open, in the reverse order of opening, and every exit path falls into the right one.
* **Each resource is closed exactly once.** A failure jumps to the label for the resources already open, and the normal path falls through all of them.

### Check your understanding

*These questions are written for this course.*

````quiz
What is the main risk of ignoring a return code in C?
○ The program won't compile.
→ Not quite. C accepts an ignored return value without a warning.
◉ The failure passes silently, and the program carries on with a wrong result.
→ Yes. Nothing stops the program when a failure is ignored.
○ The program runs twice.
→ Not quite. Ignoring a return code doesn't change how often the program runs.
````

````quiz
Why does the code set `errno = 0` before a library call?
○ So the call knows where to write its result.
→ Not quite. errno isn't an input to the call.
◉ So an old error value isn't mistaken for the reason for the new failure.
→ Yes. errno keeps its value after a success, so clearing it first makes the reading reliable.
○ To make the call faster.
→ Not quite. Clearing errno has no effect on the speed of the call.
````

````quiz
In a function with `goto close_out;` and `goto close_in;`, which label comes first in the file?
○ close_in
→ Not quite. close_out comes first, so the file opened second is closed first.
◉ close_out
→ Yes. Labels run in reverse order of opening, so the later resource is released first.
○ done
→ Not quite. done is the exit point after both resources are released.
````
