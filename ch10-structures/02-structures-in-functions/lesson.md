## Structures in functions

A structure is most useful when it travels. A function can build one and return it, receive one and read it, or receive a pointer to one and change it. The rules are the same ones you saw for values in the functions chapter, with the structure taking the place of the single value.

Here's the program for this step, in `src/main.c`. It begins with a function that builds a car:

```c
Car make_car(const char *brand, const char *model, int year) {
    Car car;
    strcpy(car.brand, brand);
    strcpy(car.model, model);
    car.year = year;
    return car;
}
```

The return type is `Car`, so the function gives back a whole car. The caller stores it like any other value:

```c
Car mine = make_car("BMW", "X5", 1999);
```

### Passing a copy

The next function receives a car as a parameter:

```c
void describe(Car car) {
    printf("%s %s %d\n", car.brand, car.model, car.year);
}
```

The parameter is an ordinary copy, as the functions chapter described. The function reads the members and prints them, and it has no way to affect the caller's car. C passes structures by value, which means the whole structure is copied. For a structure with a few members, that's cheap, and copying is the usual choice.

### Passing a pointer

The next function changes the car it receives:

```c
void make_older(Car *car) {
    car->year -= 10;
}
```

The `*` in `Car *car` makes the parameter a pointer, as the pointer parameters step described. The arrow `->` reaches a member through a pointer, and it's a shorthand for `(*car).year`. The caller passes the address:

```c
make_older(&mine);
```

After that call, the year of `mine` is 1989, since the function changed the car at that address. Use a pointer like this only when the function is meant to change the structure. Otherwise, pass a copy.

### Arrays of structures

The program then makes an array of two cars, and visits each one:

```c
Car cars[2] = {make_car("Ford", "Mustang", 1969), make_car("Fiat", "500", 2010)};
for (size_t i = 0; i < 2; i++) {
    describe(cars[i]);
}
```

An array of structures works like any other array. The index loop from the loops chapter visits each element, and `describe` receives a copy of each car, since `cars[i]` is passed by value.

The output for the whole program is:

```
BMW X5 1999
BMW X5 1989
Ford Mustang 1969
Fiat 500 2010
```

---

### Quiz

*These questions are written for this course.*

````quiz
After `make_older(&mine);`, which statement is true?
○ mine is unchanged, because make_older works on a copy.
→ Not quite. A pointer is the address of mine, so the function changes mine itself.
◉ mine.year is 10 less than before, because the function changed the car at that address.
→ Yes. The pointer gives make_older access to mine.
○ A new car is created, and mine is replaced by it.
→ Not quite. The function changes the car it was given, and creates nothing new.
````

````quiz
What does `car->year` mean when `car` is a `Car *`?
○ The address of year.
→ Not quite. The arrow reaches the member, not its address.
◉ The year member of the structure that car points to.
→ Yes. The arrow follows the pointer and reaches the member.
○ An error, because pointers can't have members.
→ Not quite. Through the arrow, a pointer reaches its structure's members.
````

---

### Try it in the runner

Change `make_older` so it takes a `Car` by value, with the body `car.year -= 10;`, and then call it with `make_older(mine);`. Predict the second line of output before you press **Run**. It's `BMW X5 1999`, since the change happened to a copy, and `mine` is unchanged. The build succeeds without any warning, which is why the choice of parameter type matters.

Then change `describe` so it takes a `Car *` and prints through the arrow. Predict what the build says about the call `describe(mine);`. It refuses it, since `mine` is a structure, and `describe` now expects an address. Restore `describe` before you continue.

---

A structure travels through a program as one value, and the parameter type decides whether a function may change it. The next step gives structures a known starting state, so each variable begins with a defined value.
