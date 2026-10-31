## Structures and functions

Structures group data, and this chapter adds behavior. In C++, a class holds the data and the functions that work on it. C keeps them apart: the data is a structure, and each function that works on it is written next to the structure and takes a pointer to it. Read together, the structure and its functions describe one kind of object, and the pointer tells each function which object it's working on.

Here's the program for this step, in `src/main.c`. The structure comes first, then a function that works on it:

```c
typedef struct {
    char brand[32];
    char model[32];
    int year;
} Car;

void car_print(const Car *car) {
    printf("%s %s %d\n", car->brand, car->model, car->year);
}
```

By convention, the function's name starts with the name of the type it works on, `car_`. That keeps related functions together when you read the file, and when you search for them. The function takes a `const Car *`, which is a pointer to a car it may read but not change. The `const` is a promise the compiler checks, so a function that claims to only read can't write by mistake.

The objects are created and set up in `main`:

```c
Car car1;
strcpy(car1.brand, "BMW");
strcpy(car1.model, "X5");
car1.year = 1999;

car_print(&car1);
```

Press **Run**. The output is:

```
BMW X5 1999
Ford Mustang 1969
```

Each car is one variable, and each call to `car_print` gets the address of the car it should print. The two cars have the same fields, but each has its own values, as the structures chapter showed.

### What C leaves out

C++ classes group data and functions inside one declaration, and the access labels say which parts the rest of the program may use. C doesn't have that. Anyone who can see the structure's declaration can read and change its fields, and `main` in this step does exactly that. The next step shows how C limits the access, and the step after it shows the init functions that set up each object.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does `car_print` take a `const Car *` rather than a `Car`?
○ Because C doesn't allow structures as parameters.
→ Not quite. C allows structure parameters, as the structures chapter showed.
◉ Because it takes a pointer to the car, so it doesn't copy the car, and const says it won't change it.
→ Yes. The pointer avoids a copy, and const makes the promise to read only.
○ Because const is required for every function.
→ Not quite. It's a choice, and the choice says what the function may do.
````

````quiz
What is the naming convention for functions that work on a `Car`?
○ Every function is named car.
→ Not quite. Several functions can work on a car, so each needs its own name.
◉ Each function's name starts with car_, the name of the type it works on.
→ Yes. The prefix groups related functions together.
○ Functions take the name of the variable they're called with.
→ Not quite. The prefix comes from the type, not from variable names.
````

---

### Try it in the runner

Set `car1.year` to `2000` directly from `main`, and predict the first line of output before you press **Run**. It prints `BMW X5 2000`, since `main` can reach every field of the structure. C has no way, in this step, to stop that. The last step of this chapter shows how to keep the fields private, and then `main` would need a function to change the year.

---

A structure and its functions describe one kind of object, with each function taking a pointer to the object it works on. The next step looks at functions that change an object, and the `const` that marks the ones that don't.
