## Ch20 · Function Pointers with Context

Many programs need a small piece of behavior in one place: a rule for sorting, a test for filtering, or an action to repeat over a list. C++ writes that as a lambda, an unnamed function written where it's needed, which can use the variables around it. C has no lambdas. It has function pointers, which pass behavior, and a `void *` argument, which passes the state the behavior needs. Together they give the same effect, with the state passed in explicitly rather than captured. This chapter covers how to pass a rule to a function, how to supply the state it uses, and what has to be kept alive while the rule runs.

The steps are:

* [Passing a rule](#goto/01-passing-a-rule): a function pointer as a rule, used the way `qsort` uses its comparison.
* [Passing state](#goto/02-passing-state): a `void *` context that carries captured values, and the lifetime rule for what it points at.
* [Summary](#goto/03-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*This chapter is written for this course. C has no lambdas or captures, so the chapter uses function pointers in place of lambdas, and a context pointer in place of captures. Nested functions are a compiler extension, not standard C, and the course avoids them.*
