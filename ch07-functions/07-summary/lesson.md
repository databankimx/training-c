## Summary: Functions

This chapter covered how a program is split into named functions, and how values move in and out of them.

* **A function is a named block of code.** It's defined with a return type, a name, parameters in parentheses, and a body in braces. `(void)` means no parameters.
* **Declare before use.** A prototype such as `void greet(void);` tells the compiler a name exists, so a call can come before the definition.
* **Arguments are copies.** Each parameter receives a copy of its argument, so a change to it leaves the caller's variable alone.
* **`return` sends a value back and ends the function.** Statements after a `return` never run.
* **One name per function.** C has no overloading, so functions that handle different types need different names.
* **An array parameter is a pointer.** The function can't find the number of elements, so the count must be passed in, and `sizeof` inside the function gives the size of the pointer.
* **Pointer parameters let a function change the caller's variables.** The caller passes `&variable`, and the function reads and writes through `*`.
* **Recursion needs a stopping point.** Each call handles a smaller part of the problem, and the recursion ends when the smaller problem is the simplest case.
* **Choose copies by default.** Pass a pointer only when the function's job is to change the caller's variable, or the value is too large to copy.

### Check your understanding

*These questions are written for this course.*

````quiz
What is the meaning of `(void)` in `int main(void)` and `void greet(void)`?
○ The function returns nothing.
→ Not quite. The void before the name means that, and the one in parentheses is about the parameters.
◉ The function takes no parameters.
→ Yes. In C, `(void)` says a function has no parameters. Empty parentheses mean something different.
○ The function is never called.
→ Not quite. A function with `(void)` can be called, and often is.
````

````quiz
After `void add_one(int value)` runs on `int number = 10;`, what is `number`?
○ 11.
→ Not quite. The function changes its own copy of the argument.
◉ 10.
→ Yes. The argument is copied, so the caller's variable is unchanged.
○ 0.
→ Not quite. Nothing sets number to 0.
````

````quiz
Why does a function that receives `int numbers[]` need a separate count parameter?
○ Because it's the only way to return a value.
→ Not quite. A count doesn't return anything.
◉ Because the function receives a pointer, and it can't find the size of the array from the pointer.
→ Yes. The size has to be passed in, since sizeof inside the function measures the pointer.
○ Because the array has to be sorted first.
→ Not quite. The order of the elements doesn't affect how the count is found.
````
