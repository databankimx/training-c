## Ch08 · Files

Every program so far has worked with values that disappear when it ends. This chapter covers files, which keep data after the program has finished. You'll write a file, read one back, and see the mistake that happens when a file is overwritten without being cleared.

The steps are:

* [Writing files](#goto/01-writing-files): creating a file with `fopen`, and checking that it opened.
* [Reading files](#goto/02-reading-files): reading a file line by line, and reading words.
* [Overwriting files](#goto/03-overwriting-files): why opening a file in append mode keeps the old text, and how to replace a file.
* [Summary](#goto/04-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*This chapter is written for this course. File functions are described in the C17 standard, in the header `stdio.h`.*
