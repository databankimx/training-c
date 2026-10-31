## Homework: Shapes

Write a small set of shapes, and a function that prints any shape's area without knowing which shape it is. C has no virtual functions, so each shape holds a pointer to its own area function, as the polymorphism step showed.

The program should:

* define a `Shape` structure with a function pointer member, `area`, which takes a `const Shape *` and returns a `double`
* give `Shape` a default area function that returns 0.0
* define `Rectangle` with a `Shape` as its first member, and `double` members `width` and `height`, and an area function that returns `width * height`
* define `Circle` with a `Shape` as its first member, and a `double` member `radius`, and an area function that uses 3.14159 for pi
* write a `make_rectangle` and a `make_circle` function, each of which sets the area pointer and the members
* define `print_area`, which takes a `const Shape *` and prints `Area: ` followed by the area with two decimal places
* in `main`, call `print_area` with a rectangle of width 3 and height 2, a circle of radius 1, and a plain `Shape`

Use `%.2f` for the printed area.

### What to check

The output should be:

```
Area: 6.00
Area: 3.14
Area: 0.00
```

The important part is that `print_area` is written once, for `Shape`, and works for all three. If the first two lines are both `0.00`, the rectangle or the circle has been given the default area function, and its pointer needs setting.

### Extensions

* Add a triangle with a base and a height, and check that `print_area` works for it without any change to `print_area`.
* Store a pointer to the wrong area function in one shape, such as the circle's pointer pointing at `rectangle_area`, and read the compiler's message. Explain what the check prevents.

---

*This exercise is not from the book. It practices the ideas in Chapter 12, with the embedding and polymorphism steps.*
