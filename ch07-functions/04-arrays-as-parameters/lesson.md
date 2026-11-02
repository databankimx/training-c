## Arrays as parameters

Passing a single `int` to a function is straightforward, and the function gets its own copy. An array is different. Copying every element into the function would be slow for a large array, so C passes an array in a different way, and that changes what the function knows about it.

Here's the program for this step, in `src/main.c`. The function's parameter is written like an array:

```c
void print_numbers(int numbers[], size_t count) {
    for (size_t i = 0; i < count; i++) {
        printf("%d\n", numbers[i]);
    }
}
```

Press **Run**. The main function calls it twice, once for all five values and once for the first three:

```c
print_numbers(my_numbers, 5);
printf("First three:\n");
print_numbers(my_numbers, 3);
```

The output is:

```
10
20
30
40
50
First three:
10
20
30
```

### The size has to be passed

The function doesn't receive the whole array. It receives only a pointer to its first element, which is the pointer from the pointers chapter. The brackets in `int numbers[]` are only a reminder of that, since the parameter is really an `int *`. From inside `print_numbers`, `numbers` is just a starting point in memory, with no record of how many elements follow it. That's why the function takes `count` as a second parameter, and why `main` passes the size each time.

This also means the tools from the arrays chapter don't help inside the function. `sizeof numbers` gives the size of a pointer, which is 8 bytes on this toolchain, not the size of the array. Dividing that by the size of one element gives a wrong count, and GCC warns about the division. Pass the count explicitly, and keep it in step with the array's real size.

### Changes reach the caller

Because the function works on the array's own elements, a change made inside it stays changed afterwards. Assigning to `numbers[0]` in the function changes the element in `main`'s array. This is the opposite of the behavior for a single `int` in the parameters step, where the function changed only its own copy. Keep it in mind when you decide whether a function should modify its input, since the caller will see the result.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does `print_numbers` take a `count` parameter?
○ Because C requires every function to have two parameters.
→ Not quite. The function has two parameters because it needs both the array and its size.
◉ Because the function receives the array's location, and it has no way to know its size.
→ Yes. The size has to be passed in, since the function sees only the first element's location.
○ To make the function run faster.
→ Not quite. The count is there so the loop knows where to stop.
````

````quiz
After `print_numbers` assigns `numbers[0] = 99;`, what does `main` see in `my_numbers[0]`?
○ 10, because the function works on a copy.
→ Not quite. The function works on the array's own elements, not a copy.
◉ 99, because the change is made to the array itself.
→ Yes. The array's elements are changed, and the caller sees the change.
○ 0, because the array is cleared on each call.
→ Not quite. Nothing clears the array.
````

---

### Try it in the runner

Add `numbers[0] = 99;` inside `print_numbers`, before the loop. Predict the output before you press **Run**. The first call changes `my_numbers[0]` to 99 and then prints it, so the first line is 99. The loop prints the rest unchanged. The second call sees the changed value, so its first line is 99 too.

Then add `printf("%zu\n", sizeof numbers / sizeof numbers[0]);` at the start of `print_numbers`, and press **Run**. The line compiles, but GCC warns that the division is wrong, since `sizeof numbers` is the size of a pointer. That's the limit described in the lesson, and the warning is the compiler pointing at it. Remove the line before you continue.

---

Passing an array to a function is how a function can work on a whole list. The next step covers pointer parameters, which let a function change a single variable in its caller, and the last step is recursion, a function that calls itself.
