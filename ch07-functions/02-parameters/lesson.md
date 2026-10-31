## Parameters

A function that always does the same thing is limited. Most functions need information from the code that calls them, and parameters are how that information gets in. A parameter is a variable named in the function's brackets, and the value passed when the function is called is its argument.

Here's the first part of this step's program, in `src/main.c`:

```c
void introduce(const char *fname, int age) {
    printf("%s is %d years old.\n", fname, age);
}
```

The function has two parameters, `fname` and `age`, each with a type. The call supplies the arguments in the same order:

```c
introduce("Scott", 53);
```

Press **Run**. The output is:

```
Scott is 53 years old.
```

Inside the function, `fname` holds the address of the text "Scott", and `age` holds 53. The function doesn't know or care where those values came from. Calling it with other arguments gives different output, from the same code.

The arguments must match the parameters in number and type. Passing the arguments in the wrong order, such as `introduce(53, "Scott")`, fails to compile, because 53 can't be used as a string pointer. The compiler reports the mismatch, and the Try section below shows you where to look.

### Parameters are copies

C passes every argument by value. The function receives a copy of each argument, and changes to a parameter change only that copy. The next part of the program shows this:

```c
void add_one(int value) {
    value = value + 1;
    printf("Inside add_one: %d\n", value);
}

int number = 10;
add_one(number);
printf("After the call: %d\n", number);
```

The output is:

```
Inside add_one: 11
After the call: 10
```

Inside `add_one`, `value` becomes 11. But `number`, in `main`, is still 10, because the function changed its own copy. This is what most people don't expect the first time, and it's the reason the next step needs pointers before a function can change a caller's variable.

C has no default values for parameters. Every call must pass every argument, and a function can't be called with one left out. If a caller usually wants the same value, the usual approach is to make the caller pass it, or to write a second function with a clearer name for that case.

---

### Quiz

*These questions are written for this course.*

````quiz
In `void introduce(const char *fname, int age)`, what is `fname`?
○ An argument.
→ Not quite. The argument is the value passed in, such as "Scott".
◉ A parameter.
→ Yes. The parameter is the name the function uses for the value it receives.
○ A return value.
→ Not quite. A return value is what a function sends back, and this one returns nothing.
````

````quiz
After `add_one(number);` runs, what is `number` in `main`?
○ 11, because the function changed it.
→ Not quite. The function changed its own copy, not the caller's variable.
◉ 10, because the function received a copy of the value.
→ Yes. Parameters are copies in C, so the caller's variable is unchanged.
○ 0, because the copy replaces the original.
→ Not quite. The original value is left alone.
````

---

### Try it in the runner

Call `introduce` with its arguments in the wrong order, as `introduce(53, "Scott")`, and press **Run**. Read the compiler's message, and look for the argument it complains about. Then put the arguments back in the right order.

Then change `add_one` so it prints `value` after the change and returns nothing, and predict whether `number` changes. It doesn't, since the function still works on its own copy.

---

Parameters let one function handle many cases, and a copy protects the caller's values. The next step covers the other half of a function's interface: the value it sends back to the caller.
