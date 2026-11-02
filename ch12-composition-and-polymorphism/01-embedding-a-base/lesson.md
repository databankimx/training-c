## Embedding a base structure

Many types share most of their data and behavior. A car is a kind of vehicle, and a sports car is a kind of car. In C++, inheritance lets a class take on the members of another class. C has no inheritance, but it has a plain way to get the same sharing: one structure contains another as a member, and the outer structure is built on the inner one.

Here's the program for this step, in `src/main.c`. The base structure comes first:

```c
typedef struct {
    char brand[32];
} Vehicle;

typedef struct {
    Vehicle base;
    char model[32];
} Car;

typedef struct {
    Car base;
    int top_speed;
} SportsCar;
```

`Car` has a `Vehicle` as its first member, named `base`, and adds its own `model`. `SportsCar` has a `Car` as its first member, and adds `top_speed`. The member is named `base` by convention, so the shared part is easy to find.

A function written for the base type takes a pointer to the base part:

```c
void vehicle_honk(const Vehicle *vehicle) {
    printf("Toot, toot!\n");
}
```

The caller passes the base part of the car, with `&my_car.base`. The function doesn't know or care what the rest of the car contains.

Press **Run**. The output is:

```
Toot, toot!
Ford Mustang
Toot, toot!
Ford Mustang 180
```

The first two lines come from `my_car`, a `Car`. The last two come from `fast`, a `SportsCar`. Each line reaches its members through the chain of `base` names: `fast.base.base.brand` is the brand of the `Vehicle` inside the `Car` inside the `SportsCar`.

### The base is the first member

The base structure is placed first in each derived structure, and that placement matters. In C, a pointer to a structure can be converted to a pointer to its first member, and the two point at the same address. The lesson's test for inheritance is therefore a layout rule: a derived type is a base type with more members after it.

The program takes that address directly, with `&fast.base.base`, which is the same as the address of `fast` itself. That's the reason the placement is kept, even though the program doesn't rely on it for any calculation here.

### Members are not copied

The derived structure contains the base's members, and the functions for the base work on the embedded copy. A change made through the base part is seen through the whole structure, because it's the same memory. In that sense the members are shared, not duplicated.

### What C leaves out

C++ inheritance also names the kind of access the derived class has, such as `public`. C has no access levels for embedded members, so every member of `Vehicle` is visible through `Car`. The next step shows how C builds a structure from more than one part, and the protection question comes with it.

---

### Quiz

*These questions are written for this course.*

````quiz
In `SportsCar fast;`, how is the brand reached?
○ fast.brand
→ Not quite. The brand is inside the Vehicle, which is inside the Car, which is inside the SportsCar.
◉ fast.base.base.brand
→ Yes. Each base member is reached in turn, down to the Vehicle that holds the brand.
○ fast->brand
→ Not quite. fast is a structure, not a pointer, so the dot is used.
````

````quiz
Why is the base structure placed first in each derived structure?
○ Because C requires it to be first.
→ Not quite. C doesn't require the base to be first, but the layout rule depends on it.
◉ So a pointer to the derived structure is also a pointer to its base part, which is the basis of the inheritance idea.
→ Yes. The first member shares its address with the structure that contains it.
○ Because the base is the smallest member.
→ Not quite. Size has nothing to do with the order.
````

---

### Try it in the runner

Add a function `vehicle_describe` that prints `A vehicle.`, and call it on `&fast.base.base`. Predict the output before you press **Run**. It prints `A vehicle.`, since `vehicle_describe` takes a `Vehicle *`, and the base part of `fast` is one.

Then change `vehicle_honk(&fast.base.base);` to `vehicle_honk(&fast);`, and predict the result. The build fails, since `&fast` is a `SportsCar *`, not a `Vehicle *`, and recent gcc versions report the mismatch as an error. Put the correct call back before you continue.

---

A derived structure contains its base as a member, and functions for the base take a pointer to that member. The next step builds a structure from more than one part.
