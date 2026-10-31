## Walkthrough: Shapes

Each shape begins with a `Shape` as its first member, so `&rect.base` and `&circle.base` are `Shape` pointers that point at the start of a larger object. `print_area` receives one of those pointers and calls `shape->area(shape)`, which runs whichever area function that shape holds. The function is written once, and it works for all three shapes.

The area functions for the rectangle and the circle receive a `const Shape *`, and they convert it back to the shape they belong to. That cast is valid only because the `Shape` is the first member, so the address is the same. The rule from the polymorphism step is what makes the cast safe, and it's why a shape's area function must always be paired with the matching structure.

The plain `Shape` uses the default function, which returns 0.0, so its line reads `Area: 0.00`. If the rectangle and the circle both printed 0.00, their pointers would still point at the default function, and the mistake would be in the constructor functions.

For the extension about a wrong pointer, the compiler checks the function's type when it's stored in the member, and an area function that takes the wrong parameter type is refused. A wrong function that does have the right type would still compile, which is why the check on the pointer's target has to be done by reading the constructor functions carefully.
