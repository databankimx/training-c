## Summary: Structures with behavior

This chapter covered how C keeps data and the functions that work on it together, and how it hides a type's fields.

* **A structure and its functions describe one kind of object.** The functions take a pointer to the object, and their names start with the type's name, such as `car_`.
* **The arrow reaches members through a pointer.** `car->year` is the year of the structure that `car` points to.
* **`const` on a pointer is a checked promise.** A `const Car *` parameter may be read but not written, and the compiler refuses a write through it.
* **Text results go into a caller's buffer.** C functions can't return an array, so a function writes its text into a buffer, with its size, for the caller to read.
* **An init function sets up an object.** C has no automatic constructor, so a function such as `car_init` fills in an object the caller has declared, and it takes every value the object needs.
* **An opaque type hides its fields.** The header declares `typedef struct Car Car;`, and only the source file that defines the structure can reach its members.
* **A setter checks each change.** The setter returns a code when it refuses a value, and it leaves the object unchanged.
* **Opaque objects are allocated and released.** `malloc` creates them and `free` releases them, and every object must be released once.

### Check your understanding

*These questions are written for this course.*

````quiz
Why does a function that only reads a `Car` take a `const Car *`?
○ Because const makes the function run faster.
→ Not quite. The keyword is about what the function may change, not speed.
◉ So the compiler checks that the function doesn't change the car, and any car can be passed to it.
→ Yes. const is a promise the compiler enforces, and it also makes the function's intent clear.
○ Because C requires const for every pointer parameter.
→ Not quite. It's optional, but it's the right choice for functions that only read.
````

````quiz
Why does `main` not know the size of a `Car` in the encapsulation step?
○ Because the size changes each time the program runs.
→ Not quite. The size is fixed for each build.
◉ Because the header declares only the type's name, so main can't declare a Car variable.
→ Yes. The members, and so the size, are defined only in car.c.
○ Because C doesn't allow structures to have a size.
→ Not quite. Every structure has a size, but main can't see it.
````

````quiz
What does `car_set_year` return when it refuses a year, and why does the caller check it?
○ 0, because a refused year is stored anyway.
→ Not quite. 0 means the year was stored.
◉ -1, so the caller knows the change didn't happen and can report it.
→ Yes. The return value is the only report of the refusal in C.
○ It throws an exception that the caller must catch.
→ Not quite. C has no exceptions, so the refusal is a return value.
````
