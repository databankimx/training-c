## Structures as variables

A variable holds one value. Often a program needs several values that belong together: a car has a brand, a model, and a year, and those three values travel as one thing. A structure groups them under one name, and each value inside it is a member.

Here's the program for this step, in `src/main.c`. The structure is declared once, at the top of the file:

```c
typedef struct {
    char brand[32];
    char model[32];
    int year;
} Car;
```

The declaration creates a new type, `Car`, in the same way `int` and `char` are types. It doesn't create any cars. It describes what a car contains: a brand, a model, and a year. Declare it outside `main`, so every function can use it.

The word `typedef` gives the structure a short name. Without it, every variable would need the full form, `struct { ... } car`, and the type would have no name to pass to a function. The brackets after `brand` and `model` are fixed-size character arrays, which hold the text. C has no `std::string`, so the program decides the largest size each member needs, here 31 characters and a zero byte.

Create a variable of the type, and set its members with a dot:

```c
Car my_car1;
strcpy(my_car1.brand, "BMW");
strcpy(my_car1.model, "X5");
my_car1.year = 1999;
```

The text members are filled with `strcpy`, which copies a string into an array. The year is a plain assignment. The program makes a second car the same way, and prints both:

```c
printf("%s %s %d\n", my_car1.brand, my_car1.model, my_car1.year);
printf("%s %s %d\n", my_car2.brand, my_car2.model, my_car2.year);
```

Press **Run**. The output is:

```
BMW X5 1999
Ford Mustang 1969
```

Each car is one variable, and its members are reached through the dot. `my_car1.brand` is the brand of the first car, and `my_car2.year` is the year of the second. The two cars have the same members, but each car has its own values.

### Members have their own types

Each member has its own type, and the compiler checks every assignment against it. `my_car1.year = "1999";` won't compile, since `year` is an `int` and the string is a pointer. The structure's declaration is the record of those types, so you can read it to see what each member expects.

### Text members must fit

`strcpy` copies every character of the string and the zero byte after it. If the text is longer than the array, `strcpy` writes past the end of the member, into whatever follows it in memory. The strings chapter described this risk. Choose a size large enough for the longest value the program will store, or use `snprintf` with the member's size, which stops before the end.

---

### Quiz

*These questions are written for this course.*

````quiz
What does the declaration `typedef struct { ... } Car;` create?
○ A car, ready to use.
→ Not quite. It describes a car, but it doesn't create one.
◉ A new type called Car, which variables can be made from.
→ Yes. typedef gives the structure a name, and variables of that name can be declared.
○ A function that prints a car.
→ Not quite. A structure is data, not a function.
````

````quiz
How do you set the year of `my_car1`?
○ my_car1->year = 1999;
→ Not quite. The arrow is for pointers, and my_car1 is a variable.
◉ my_car1.year = 1999;
→ Yes. A dot reaches a member of a structure variable.
○ Car.year = 1999;
→ Not quite. The dot works on a variable, not on the type's name.
````

---

### Try it in the runner

Add a member `char color[32];` to `Car`. Then print `my_car1.color` without setting it, and predict the output before you press **Run**. In C, a local structure isn't zero-filled, so the member holds whatever was in memory before, and the printed text may be garbage. That's different from C++, where an unset `std::string` starts empty. Now set `my_car1.color` with `strcpy`, and check that the output is correct.

Then set `my_car1.year` to `"1999"`, in quotes, and press **Run**. The build fails, because `year` is an `int`, and a string can't be stored in it.

---

A structure gives a name to a group of values, and each member has its own type. The next step passes structures to functions, and returns them from functions, which lets a program move a whole group of values at once.
