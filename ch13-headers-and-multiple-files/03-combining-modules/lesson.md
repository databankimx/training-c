## Combining modules across files

This step puts the chapter together. Three modules live in three pairs of files, and one of them is built from the other two. Each module is small, and each file does one job. The program is spread across seven files, but the design is the one from the composition chapter: an electric car is a car, and it has a battery.

The relationships are the ones the C++ version expresses with inheritance and a member, and the files make them visible:

* `electric_car.h` includes `car.h`, because the electric car contains a car as its first member, `base`.
* `electric_car.h` includes `battery.h`, because the electric car contains a battery as its `battery` member.

Here's the structure that holds both:

```c
typedef struct {
    Car base;
    Battery battery;
} ElectricCar;
```

The `base` member is the car, as the composition chapter showed, and it's first, so a pointer to the electric car is also a pointer to its car. The `battery` member is a `Battery` structure, built with the electric car.

### The init function builds the parts

C has no base-class constructor, so the init function builds each part in turn. The C++ version writes the base constructor's arguments after a colon. In C, the same work is written in the body, in the order the parts must be ready:

```c
void electric_car_init(ElectricCar *electric, const char *make, const char *model, int year, int charge) {
    strcpy(electric->base.make, make);
    strcpy(electric->base.model, model);
    electric->base.year = year;

    battery_init(&electric->battery, 100, 0);
    if (charge > 0) {
        battery_recharge(&electric->battery, charge);
    }
}
```

The car's fields are set first, because the car is the base part and has to be complete before the rest of the electric car is set up. The battery comes next, with a capacity of 100 and no charge, and then the starting charge is added if one was given.

### What the program prints

Press **Run**. The output is:

```
Make: Ford
Model: Escort
Year: 1986

Make: Nissan
Model: Leaf
Year: 2015

Charge: 25
Capacity: 100

Charge: 50
Capacity: 100

Charge: 100
Capacity: 100

```

The first two blocks come from the car functions, and the last three from the battery through `electric_car_show_charge`. Each `electric_car_charge` call changes the battery and nothing else. The call with zero fills the battery, which is the rule from the include-guards step.

### Which header includes which

Each header includes only what its own declarations need. `car.h` includes nothing. `battery.h` includes nothing. `electric_car.h` includes both, since its structure contains a `Car` and a `Battery`. The `.c` files include their own headers, so the compiler checks each definition against its declaration. Keeping these links small is what lets the program grow without every file depending on every other.

---

### Quiz

*These questions are written for this course.*

````quiz
In `electric_car_init`, why are the car's fields set before the battery?
○ Because C requires the battery to be set last.
→ Not quite. C has no rule about the order of unrelated members.
◉ Because the car is the base part, and it should be complete before the rest of the electric car is set up.
→ Yes. Building parts in order means each part is ready before the next one is set.
○ Because the battery depends on the car's make.
→ Not quite. The battery doesn't use the car's fields.
````

````quiz
Why does `electric_car.h` include both `car.h` and `battery.h`?
○ Because headers must include every header in the program.
→ Not quite. A header includes only what its own declarations need.
◉ Because ElectricCar contains a Car and a Battery, so both types must be declared.
→ Yes. The compiler needs both declarations to lay out ElectricCar.
○ Because one of them is a system header.
→ Not quite. Both are the course's own headers.
````

---

### Try it in the runner

Call `electric_car_charge(&tesla, 200)`, and predict the charge shown afterwards. The battery is capped at its capacity of 100, so the output is `Charge: 100`.

Then call `electric_car_charge(&tesla, -5)`, and predict the result. The battery has no check for a negative amount, so the charge drops to 95. That's a real weakness of the module, and a good prompt for thinking about where validation belongs.

---

Three modules, seven files, and a clear picture of which part depends on which. The summary covers the chapter's file rules, and the homework builds a small multi-file program of your own.
