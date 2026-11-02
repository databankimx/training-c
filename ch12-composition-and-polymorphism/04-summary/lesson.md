## Summary: Composition and polymorphism

This chapter covered how C builds one type from another, and how a single call can do different work for different objects. C has no inheritance and no virtual functions, so these are done with structures and function pointers.

* **A structure can contain another as its first member.** `Car` holds a `Vehicle` as `base`, and `SportsCar` holds a `Car`. Each level adds its own members.
* **Members are reached through the chain of parts.** `fast.base.base.brand` names the brand inside the innermost part.
* **The base is placed first.** A pointer to the outer structure is also a pointer to its first member, which is the basis of treating a derived type as its base.
* **A structure can hold several parts.** Each part keeps its own members, and the path through the part names the one meant.
* **C has no protected level.** Protection is a convention, or it comes from defining the structure in one source file, as an opaque type does.
* **A function pointer gives each object its own behavior.** A call through `animal->sound(animal)` runs the function that the object holds, which is the C form of a virtual call.
* **The compiler checks the function's type.** A function with the wrong parameters is refused when it's stored in the member, which is how C checks what `override` checks in C++.
* **Pass the object by pointer.** A pointer to the object keeps its whole contents, so the function that the object holds is still the one that runs.

### Check your understanding

*These questions are written for this course.*

````quiz
In `SportsCar fast;`, which member holds the brand?
○ fast.brand
→ Not quite. The brand is inside the Vehicle, two parts down.
◉ fast.base.base.brand
→ Yes. The path goes through each embedded part to the Vehicle that holds the brand.
○ fast->base.brand
→ Not quite. fast is a structure, not a pointer, so the dot is used.
````

````quiz
What is the C form of a virtual function call?
○ Calling a function by its name in the base structure.
→ Not quite. A named call always runs the same function.
◉ Calling through a function pointer that the object itself holds.
→ Yes. The object's pointer decides which function runs.
○ Declaring the function with the keyword virtual.
→ Not quite. C has no virtual keyword.
````

````quiz
Why does C place the base structure first in a derived structure?
○ Because the compiler requires it to be first.
→ Not quite. The compiler doesn't require it, but the layout rule depends on it.
◉ Because a pointer to the derived structure is also a pointer to its base part.
→ Yes. The first member shares its address with the structure that contains it.
○ Because the base is the largest member.
→ Not quite. Size has nothing to do with the order.
````
