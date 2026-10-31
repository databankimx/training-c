## Init functions

C++ has constructors, which are special functions that run when an object is created, and they set the object's members so that every object starts in a valid state. C has no constructors, and no call that runs automatically when an object is declared. The C form is an ordinary init function, named for its type, that fills in an object the caller has already declared.

Here's the function for this step, in `src/main.c`:

```c
void car_init(Car *car, const char *brand, const char *model, int year) {
    strcpy(car->brand, brand);
    strcpy(car->model, model);
    car->year = year;
}
```

The function takes a pointer to the object it sets up, and the values that the object needs. The body copies each value into its member, so the object is complete when the function returns. The caller declares the object first, and then calls the function on it:

```c
Car my_car1;
car_init(&my_car1, "Ford", "Mustang", 1969);
car_show(&my_car1);
```

Press **Run**. The output is:

```
1969 Ford Mustang
2014 Dodge Challenger
```

Both cars are created the same way, with an object declared and then initialized. The function `car_show` prints one car, and it takes a `const Car *`, as the methods step described.

### Why the caller declares the object

In C++, the constructor can create the object, because the compiler knows how big an object is and where to put it. C's `car_init` works on an object that already exists, and the caller provides its storage. That's why the caller declares `my_car1` on its own line before the call. The same approach is what lets a C function set up an object without returning it. The structures chapter showed the other approach, a function that returns a whole structure, and either one is a valid way to set up an object in C.

### Requiring every value

An init function is useful because it forces every object to be set up with the values it needs. In C, the function's parameter list does that job. `car_init` takes a brand, a model, and a year, so a call that leaves one out doesn't build:

```c
car_init(&my_car3, "Fiat");
```

The compiler reports that the call has too few arguments. An object that was declared but never passed to `car_init` still has no defined values, which is the risk the structures chapter described, so every object should go through its init function.

### Brace initialization in C

The structures chapter used braces to set members in order, as `Settings b = {"Scott", 9, true};`. That still works here, and it doesn't call `car_init`. The braces set the members directly, with no function involved, so a program that wants every object checked should use the init function, and use braces only for simple structures with no rules to enforce.

### What C leaves out

C++ can build a class that inherits from another, and its constructor passes arguments to the base class's constructor. C has no inheritance, so that part of the C++ lesson is not repeated here. Chapter 12 shows the C way to build a similar structure, using function pointers.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `car_init` do with the object it receives?
○ It creates a new object and returns it.
→ Not quite. It fills in an object the caller has already declared.
◉ It copies the values into the object's members, so the object is complete when the function returns.
→ Yes. The pointer lets the function set the members of the caller's object.
○ It prints the object's values.
→ Not quite. That's car_show. car_init sets the values.
````

````quiz
Why does the caller declare `my_car1` before calling `car_init`?
○ Because C requires every variable to be declared on its own line.
→ Not quite. The declaration can share a line, and the rule isn't about lines.
◉ Because C's init function works on an object that already exists, so the caller provides its storage.
→ Yes. The object must exist before the function can fill it in.
○ Because car_init can't take a pointer to an object that hasn't been declared.
→ Not quite. A pointer is needed, but the point is that the object must exist first.
````

---

### Try it in the runner

Declare `Car my_car3;` and call `car_init(&my_car3, "Fiat", "500", 2010);` followed by `car_show(&my_car3);`. Predict the output, and press **Run**. It prints `2010 Fiat 500`.

Then call `car_init(&my_car3, "Fiat");` with only one value after the object, and press **Run**. The build fails, since `car_init` takes four arguments. Restore the call before you continue.

---

An init function sets an object's members when it's created, so each object starts in a known state. The next step restricts access to members, so that the only way to change an object is through the functions the module provides.
