## Homework: Rectangle scale

Write a program that uses a structure to describe a rectangle, and scales it with a function.

The program should:

* define a structure called `Rectangle`, with two `double` members, `width` and `height`
* define `area`, which takes a `Rectangle` by value and returns `width * height`
* define `scale`, which takes a pointer to a `Rectangle` and a `double` factor, and multiplies both members by the factor
* in `main`, create a rectangle with `Rectangle r = {3.0, 2.0};`, print its area, call `scale(&r, 2.0)`, and print its area again
* print each area with a label, such as `Area: 6.00`, using two decimal places

### What to check

For the rectangle in the sample, the output should be:

```
Area: 6.00
Area: 24.00
```

The second area should be four times the first, since scaling both sides by 2 multiplies the area by 4. Check that `area` doesn't change the rectangle, and that `scale` does.

### Extensions

* Create a second rectangle with only its width set, `Rectangle s = {4.0};`, and print its area. What is the height, and why?
* Make `scale` refuse a factor of zero or less, with a message. Decide whether a zero scale is an error, or a valid result that the caller should know about.

---

*This exercise is not from the book. It practices the ideas in Chapter 10, with the functions and pointers from Chapters 5 and 7.*
