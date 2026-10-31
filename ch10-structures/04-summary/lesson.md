## Summary: Structures

This chapter covered how related values are grouped under one type, how functions use that type, and how each variable starts in a known state.

* **`typedef` names a structure type.** `typedef struct { ... } Car;` lets variables be declared as `Car`, without writing `struct` each time.
* **Members are reached with a dot.** `car.year` is the year of a structure variable.
* **Each member has its own type.** The compiler checks every assignment against the declaration.
* **Text members are fixed-size arrays.** They're filled with `strcpy`, and the size must fit the longest value.
* **A structure is passed by value.** A function receives a copy, so changes inside it don't reach the caller.
* **A pointer reaches the caller's structure.** The caller passes `&car`, and the function changes it through `car->year`.
* **Structures can be returned.** A function returns a whole structure, which the caller stores like any other value.
* **Brace initialization sets members in order.** The values must match the declared types, and members left out are zero.
* **A function can hold the defaults.** C has no default member values, so a function that returns a complete structure does that job.
* **A copy is independent.** Changing a copied structure never changes the original.

### Check your understanding

*These questions are written for this course.*

````quiz
What is `car->year` when `car` is a pointer to a `Car`?
○ The address of the year member.
→ Not quite. The arrow reaches the member's value.
◉ The year member of the structure that car points to.
→ Yes. The arrow follows the pointer to the structure, then reaches the member.
○ A copy of the whole car.
→ Not quite. The arrow reaches one member, and copies nothing.
````

````quiz
After `Settings b = {"Scott", 9, true}; Settings c = b; c.volume = 1;`, what is `b.volume`?
○ 1, because c shares b's memory.
→ Not quite. c is a separate copy, with its own memory.
◉ 9, because changing c leaves the original unchanged.
→ Yes. A copy is a separate structure, and changes to it stay in the copy.
○ 0, because copies start empty.
→ Not quite. A copy starts with the same values as the original.
````

````quiz
What does `Settings s = {0};` set `volume` to, if `volume` is an `int` member?
○ 5, the usual default.
→ Not quite. C doesn't apply defaults from the declaration.
◉ 0, because members left out of an initializer are set to zero.
→ Yes. Zeroing is the rule for members the braces don't set.
○ An unknown value, because a structure isn't initialized.
→ Not quite. Brace initialization always sets the members it doesn't list to zero.
````
