## Hiding fields

Access control decides which parts of the program can use a class's members. Encapsulation is the design that follows from it: an object keeps its data private, and changes the data only through functions that check each change. C has no `private:` label, so it uses a different tool to get the same result. The structure is defined in one source file, and the rest of the program sees only a declaration of it. That declaration is an opaque type.

This step has three files. The header declares the type and its functions, and the source file defines the structure and does the work:

```c
/* car.h */
typedef struct Car Car;
Car *car_create(const char *brand, const char *model, int year);
int car_set_year(Car *car, int year);
```

The header says `typedef struct Car Car;` and stops there. It names the type without giving its members, so code that includes the header can hold a `Car *`, but it can't read `car->year`. Only `car.c`, which defines `struct Car`, can reach the fields.

Press **Run**. The output is:

```
1969 Ford Mustang
2014 Ford Mustang
year is before cars existed
2014 Ford Mustang
```

### The setter checks the value

The setter is where the rule lives. Here's `car_set_year` from `car.c`:

```c
int car_set_year(Car *car, int year) {
    if (year < 1886) {
        return -1;
    }
    car->year = year;
    return 0;
}
```

A year before 1886 is refused, since no car existed before then. The function returns -1 and leaves the car unchanged, so the object keeps its last valid year. The caller checks the return value, as the return-codes step described. C has no exceptions, so this is where the C++ version used a thrown error.

The setter returns 0 when the year is stored. The program in `main.c` tests that value, which is why the message appears only for the refused year, and the last line still shows 2014.

### The init function uses the setter

`car_create` allocates the car, copies the text, and then calls `car_set_year` for the year, rather than assigning the field directly:

```c
if (car_set_year(car, year) != 0) {
    free(car);
    return NULL;
}
```

That way, the same check applies to an object's first value as to every later change. An init function that wrote the field directly could create a car with a year the setter would refuse.

### Why the object is on the heap

`main` holds a `Car *` and doesn't know how big a `Car` is, because the size of an opaque type isn't in the header. So the object can't be declared as a local variable in `main`, and `car_create` allocates it with `malloc` instead. `car_destroy` releases it with `free`. Dynamic memory is covered properly in the containers chapter. For now, the rule is simple: every object from `car_create` must be passed to `car_destroy` once, when the program no longer needs it.

### Why keep data private

Private data can be changed in one place, the source file that defines the structure, so a rule written there applies everywhere. If `main` could write `car->year` directly, every part of the program would have to remember the rule. The header and the setter keep it in one place.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does `car.h` declare `typedef struct Car Car;` without the members?
○ Because the compiler requires the members to be in the source file.
→ Not quite. The members can go in a header, but the design hides them from other code.
◉ So other files can use a Car pointer, but can't read or change the fields directly.
→ Yes. The members are visible only in car.c, so the rules stay there.
○ Because structures can't be declared in headers.
→ Not quite. They can be, but this design deliberately keeps the members out.
````

````quiz
What does `car_set_year` return when it refuses a year?
○ 0, because the refused year is stored anyway.
→ Not quite. 0 means the year was stored, which is not the case here.
◉ -1, and the car is left with its last valid year.
→ Yes. The caller checks the return value, and the car is unchanged.
○ NULL.
→ Not quite. car_set_year returns an int, not a pointer.
````

---

### Try it in the runner

Add `my_car->year = 1700;` to `main.c`, and predict whether it builds before you press **Run**. It doesn't. `main.c` sees only the declaration of `Car`, so the compiler reports that it can't use the fields of an incomplete type. Remove the line before you continue.

Then change the year in `car_set_year` so that 1800 is accepted, and predict the third line of output for `car_set_year(my_car, 1700)`. It's the same, since 1700 is still refused. Restore the original check before you continue.

---

An opaque type hides an object's fields behind its source file, and the setter keeps the object within its rules. The summary and homework ask you to build a small type of your own, using this design.
