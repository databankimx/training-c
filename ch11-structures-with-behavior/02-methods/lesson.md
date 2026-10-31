## Functions that act on an object

In C++, a method is a function that belongs to a class and works on the object it's called on. C has no methods. The same job is done by a function that takes a pointer to the object, and the object's members are reached through the arrow, as in `car->brand`. The function is still written next to its structure, and its name starts with the type's name.

Here's the program for this step, in `src/main.c`. Both functions take a `const Car *`:

```c
void car_name(const Car *car, char *out, size_t size) {
    snprintf(out, size, "%s %s", car->brand, car->model);
}

void car_full_name(const Car *car, char *out, size_t size) {
    snprintf(out, size, "%d %s %s", car->year, car->brand, car->model);
}
```

Press **Run**. The output is:

```
Ford Mustang
1969 Ford Mustang
```

The two functions read the same fields, and each formats them differently.

### Text results go into a buffer

A C++ method can return a `std::string`. A C function can't return an array, so the text is written into a buffer the caller provides. The buffer is the `out` parameter, and `size` tells `snprintf` how much room it has, so the text can't overflow it. The caller declares the buffer and passes it in:

```c
char text[80];
car_name(&my_car, text, sizeof text);
printf("%s\n", text);
```

The same buffer can be reused for the second function, because the first result has already been printed.

### const on the pointer

The `const` in `const Car *car` is the C form of the `const` after a C++ method's parentheses. It promises that the function reads the car and doesn't change it. The compiler checks the promise: a write through a `const` pointer is an error, not a warning. A function that only reports the car's state should always take a `const` pointer, so a caller can pass any car, including one the caller never intended to change.

The `car_` prefix groups these functions with their structure, as the previous step showed.

---

### Quiz

*These questions are written for this course.*

````quiz
Why do `car_name` and `car_full_name` take a `char *out` buffer?
○ Because C functions can't use the printf function.
→ Not quite. Both functions print nothing, and they use snprintf.
◉ Because a C function can't return an array, so the text is written into a buffer the caller provides.
→ Yes. The caller declares the buffer and passes it in, and the function fills it.
○ Because strings are always passed by reference in C.
→ Not quite. C strings are pointers, but the buffer is needed because the result must be stored somewhere the caller can read.
````

````quiz
What does `const Car *car` promise about the function that takes it?
○ That the function returns a constant value.
→ Not quite. It describes what the function may do to the car, not what it returns.
◉ That the function reads the car and doesn't change it, and the compiler checks the promise.
→ Yes. A write through a const pointer is an error.
○ That the car can be used only once.
→ Not quite. A const pointer can be used any number of times.
````

---

### Try it in the runner

Add `car->year = 2000;` inside `car_name`, and predict whether the build succeeds before you press **Run**. It fails, since `car` is a `const Car *`, and the compiler refuses to change the car through it. Remove the line before you continue.

Then remove the `const` from the parameter of `car_name`, and add the same line. Predict whether the build succeeds now. It does, since the promise has been taken away, and the function may change the car. That's why the `const` matters: it lets a reader trust a function from its signature alone.

---

A method in C is a function that takes a pointer to the object, and `const` on that pointer is the promise that the function only reads. The next step covers init functions, the functions that set up each object when it's created.
