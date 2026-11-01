## Summary: Generic code

This chapter covered writing one routine for many types. C has no templates, so the chapter used two techniques: a macro that the preprocessor expands, and functions that work on `void *` pointers with the size of an element and a comparison supplied by the caller.

* **A macro is text, substituted before compilation.** It works for any type that supports the operations it uses, but it isn't type-checked.
* **A macro can evaluate an argument more than once.** Arguments with side effects, such as calls that count or change state, can run several times.
* **Parenthesize macro parameters and the whole expansion.** Without them, operators in the arguments mix with the surrounding code.
* **A function is safer than a macro for ordinary values.** It evaluates each argument once and is type-checked.
* **A void pointer carries no type.** A generic function must be given the size of one element.
* **The caller supplies the comparison.** A function pointer decides what counts as equal, and the programmer writes one per type.
* **The compiler can't check a generic function's types.** A wrong size or a wrong comparison compiles, and the mistake shows up only at run time.
* **The element size must match the array.** Using `sizeof` of one element keeps the two in step.

### Check your understanding

*These questions are written for this course.*

````quiz
Why can a macro give a different result from a function, when an argument has a side effect?
○ Because macros are always faster.
→ Not quite. Speed isn't the reason for the different results.
◉ Because a macro can repeat the argument's text, so the side effect can happen more than once.
→ Yes. A function evaluates each argument once before the call.
○ Because functions cannot take a call as an argument.
→ Not quite. Functions take calls as arguments all the time.
````

````quiz
What must a generic function that works on `void *` be told about each element?
○ Its name.
→ Not quite. The name doesn't tell the function how many bytes to move.
◉ Its size in bytes, and a comparison function to decide equality.
→ Yes. The size tells the function how much to move, and the comparison decides which elements match.
○ Its type, as a string.
→ Not quite. C has no way to pass a type as a value, so the size is passed instead.
````

````quiz
Which check does the compiler make for a call to a `void *` generic function?
○ It checks that the element size matches the array.
→ Not quite. The compiler accepts any size, since the parameter is a plain size_t.
◉ It checks only that the pointer arguments are pointers, so the caller must check the rest.
→ Yes. The rest of the correctness is the programmer's responsibility.
○ It checks that the comparison function returns the right type for each element.
→ Not quite. It checks the function pointer's type, not what the function does with the elements.
````
