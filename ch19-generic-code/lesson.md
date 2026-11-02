## Ch19 · Generic Code

The same algorithm often works for many types: finding the larger of two values, storing a pair, holding a list. C++ templates let you write the code once, with the type left as a placeholder, and the compiler generates a version for each type the program uses. C has no templates. It has three ways to get the same effect, and each has a cost. This chapter covers them: a macro that is expanded by the preprocessor, a function that works on `void *` pointers with the size of each element passed in, and a comparison function that the caller supplies, which is the approach `qsort` takes.

The steps are:

* [Macros](#goto/01-macros): a function-like macro, its safe use, and why its arguments can be evaluated twice.
* [Void pointers and element sizes](#goto/02-void-pointers): one function that works on any type, given the size of an element and a comparison.
* [Summary](#goto/03-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*This chapter is written for this course. C has no templates, so the chapter uses macros and `void *` with element sizes, in place of the C++ function and class templates.*
