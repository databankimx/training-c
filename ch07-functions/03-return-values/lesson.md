## Return values

A function that only prints is useful, but many functions are better at calculating something and handing the result back. A function that returns a value gives its caller a result to store, print, or use in another calculation.

Here's the first part of this step's program, in `src/main.c`:

```c
int add_five(int x) {
    return 5 + x;
}
```

The `int` before the name is the return type. It says the function gives back an `int`. The `return` statement sends the value back to the caller, and it also ends the function at that point. Nothing after a `return` runs.

The program calls the function and uses its result:

```c
int res = add_five(3);
printf("%d\n", res);
```

The output is `8`. The call `add_five(3)` is replaced by its result, 8, which is then stored in `res`. A function call can appear anywhere a value of its return type can appear, so you can print it, store it, or put it inside another expression.

A function that gives nothing back uses `void` as its return type, as the first step did. `void` means there's no result to use, so a call to a `void` function can't be the right-hand side of an assignment. The compiler refuses it.

### One name per function

The program has two functions that add numbers, and they have different names:

```c
int add_ints(int x, int y) {
    return x + y;
}

double add_doubles(double x, double y) {
    return x + y;
}
```

C++ allows two functions to share a name when their parameters differ, which is called overloading. C doesn't allow it. Every function needs its own name, so the program calls `add_ints` for whole numbers and `add_doubles` for decimals:

```c
int whole = add_ints(8, 5);
double decimal = add_doubles(4.3, 6.26);
printf("Int: %d\n", whole);
printf("Double: %.2f\n", decimal);
```

The output is:

```
Int: 13
Double: 10.56
```

The `%.2f` prints the `double` with two places after the point. The name tells the reader which version runs, and the compiler never has to choose between them. If you give two functions the same name in C, the compiler reports a conflicting definition and refuses the program.

Choosing a name for each version is a small cost, and the names say what each function does. The cost is paid back the first time you read the code and don't have to work out which overload a call means. C has a way to write one function that works for several types, using `_Generic`, which appears in the generic code chapter later in the course.

---

### Quiz

*These questions are written for this course.*

````quiz
What happens to the statements after a `return` in a function?
○ They run, and then the function returns.
→ Not quite. return ends the function at that point.
◉ They don't run, because the function has already finished.
→ Yes. return leaves the function immediately.
○ They run only if the function has no return value.
→ Not quite. A return always ends the function, whatever its type.
````

````quiz
What happens if two functions in a C program have the same name and different parameters?
○ The compiler picks the one that matches the arguments.
→ Not quite. That's overloading, which C doesn't have.
◉ The compiler reports a conflicting definition and refuses the program.
→ Yes. C requires every function to have its own name.
○ The program runs, and the later definition replaces the earlier one.
→ Not quite. The compiler stops at the second definition.
````

---

### Try it in the runner

Call `add_ints(8, 5.0)`, which passes a `double` where an `int` is expected, and predict the result before you press **Run**. The `5.0` is converted to `5`, so the sum is 13, and the function works. Then add a second definition named `add_ints` that takes two `double` values, and press **Run**. The compiler refuses the second definition, as the last section described. Remove it before you continue.

---

A function can take values in and give a result back, and a clear name tells the reader which version does the work. The next step uses arrays, which are harder to pass to a function than a single value, and the size of the array becomes something the function has to be told.
