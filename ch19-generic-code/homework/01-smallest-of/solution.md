## Walkthrough: Smallest of

`smallest_of` starts with the first element, and each later element is compared with the smallest so far, using the caller's comparison. Because it only ever reads elements from `base` up to `count`, it never reads past the end.

The element size decides which bytes are read. For the string array, the size is `sizeof words[0]`, which is the size of a pointer, since each element is a `const char *`. The comparison then reads that pointer and compares the text. Using the size of the text instead would read the wrong bytes.

The empty case returns `NULL`, rather than reading an element that doesn't exist. The caller must check for `NULL` before it dereferences the result, as the program does. A template would not catch this: the empty array is a run-time condition, and the check has to be written.
