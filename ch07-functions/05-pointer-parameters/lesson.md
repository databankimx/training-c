## Pointer parameters

The parameters in this chapter so far have each received a copy of the caller's value. Changing a copy inside the function leaves the caller's variable alone. That's the right behavior most of the time, but some jobs need to change the caller's variables, and a swap is the classic example. A pointer parameter gives the function the address of the caller's variable, so the function can reach the variable itself.

Here's the program for this step, in `src/main.c`:

```c
void swap_nums(int *x, int *y) {
    int z = *x;
    *x = *y;
    *y = z;
}
```

The `*` before each name makes it a pointer, as the pointers chapter described. Inside the function, `*x` is the value at the address the caller passed in, so assigning to `*x` changes the caller's variable. The caller passes addresses with `&`:

```c
swap_nums(&first, &second);
```

Press **Run**. The output is:

```
10 20
20 10
```

The first line is printed before the call, and the second after it. The swap ran on the variables `main` owns, so their values have changed.

C has no reference parameters, which C++ uses for the same job. A pointer does the same work, but the call site shows it: `&first` tells the reader that `first` may be changed. The function's body shows the rest, since each use of a pointer parameter goes through `*`.

### Copy or pointer

Compare this with the earlier parameters. In `introduce(const char *fname, int age)`, the function receives copies of its values, so changing `age` inside it would have no effect outside. The `*` in `int *x` is the only difference between a parameter that copies and one that reaches the caller's variable.

Choose the copy by default. It keeps the function from changing things it wasn't asked to change, and it makes the function's effect easier to see from its call. Use a pointer when the job is to change the caller's variable, or when the value is large and copying it would be wasteful. The `const` in `const char *` from the strings step is the usual way to show that a pointer parameter only reads.

### Why a swap needs pointers

If the function had ordinary `int` parameters, and the same body, the swap would happen inside the function and disappear when it returns. `main` would print the original values again. The program would build without any warning, which is why the pointer matters. Check what a function changes, and what it's meant to change.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does the swap need pointer parameters?
○ Because pointers make the swap faster.
→ Not quite. The reason is what the function can change, not speed.
◉ Because the function must change the caller's variables, not copies of them.
→ Yes. A pointer gives the function the address of the caller's variable.
○ Because the swap won't compile with ordinary parameters.
→ Not quite. It compiles, but the caller would see no change.
````

````quiz
In `swap_nums(&first, &second);`, what does `&first` pass to the function?
○ A copy of first's value.
→ Not quite. The & operator gives the address, not a copy.
◉ The address of first, which the function can read and change through.
→ Yes. The function receives a pointer to the caller's variable.
○ The name first, as text.
→ Not quite. C passes addresses, not names.
````

---

### Try it in the runner

Write a second function, `swap_copies(int x, int y)`, with the same body but no pointers. Call it from `main` with `first` and `second`, and predict what `main` prints afterwards. The values don't change, since the function swapped its own copies. The program builds without any warning, which is the silent bug the lesson describes. Remove the function and its call before you continue.

---

Pointer parameters let a function change its caller's variables. The last step is recursion, a function that calls itself.
