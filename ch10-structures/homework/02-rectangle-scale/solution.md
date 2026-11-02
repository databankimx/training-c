## Walkthrough: Rectangle scale

`area` receives a copy of the rectangle and multiplies its two members, so it can't change the caller's rectangle. That's why the program can print the area and then scale the same rectangle without any surprise.

`scale` receives a pointer, and it multiplies the members through `->`. The caller passes `&r`, so the changes land in `r` itself. Scaling both sides by 2 multiplies the area by 4, which is why the second line is 24.00 when the first is 6.00.

The extension about a rectangle with only its width set has a C answer that differs from the C++ one. C doesn't give members default values, so the members left out of the braces are zero. The height is 0, and the area is 0.00. A program that needs 1.0 as the default writes it in the braces, as `Rectangle s = {4.0, 1.0};`, or in a function that builds rectangles, as the Chapter 10 structures step did.

For the zero-factor extension, the choice is between an error and a valid result. A factor of zero collapses the rectangle to a line with no area, which is a real result, and the caller may need to know about it. Returning a code from `scale` or checking the factor in `main` both work, and the return-codes step described the approach.
