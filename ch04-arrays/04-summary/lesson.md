## Summary: Arrays

This chapter covered how a program stores a list of values of one type under a single name.

* **An array holds many values of one type.** It's declared with a type, a name, and a size in square brackets, such as `int nums[3]`.
* **Indexes start at zero.** `nums[0]` is the first element, and `nums[2]` is the third. Each index must be within the array.
* **Elements can be read and changed.** `nums[2] += 5` works just like a variable.
* **Going past the end is undefined.** C doesn't check indexes, so a bad index can give garbage, a crash, or a bug that appears somewhere else.
* **Partly filled arrays are zero-filled.** Elements without a listed value are zero for numbers and for characters.
* **Leave out the size when you list the values.** `int speeds[] = {...}` counts the values for you.
* **`sizeof` gives the number of elements.** `sizeof array / sizeof array[0]` divides the array's size in bytes by the size of one element. It works only while the array's declaration is in view.
* **Multidimensional arrays use one index per dimension.** `grid[1][2]` is row 1, column 2. Both indexes start at zero, and each must stay within its own size.

### Check your understanding

*These questions are written for this course.*

````quiz
Which index refers to the last element of `int nums[4]`?
○ 4
→ Not quite. That's one past the end of a four-element array.
◉ 3
→ Yes. Indexes run from 0 to 3, so the last element is at index 3.
○ 2
→ Not quite. That's the third element.
````

````quiz
For `int speeds[] = {60, 75};`, what does `sizeof speeds / sizeof speeds[0]` give?
○ 1
→ Not quite. That would be the index of the last element.
◉ 2
→ Yes. The array has two elements, so the division gives 2.
○ 8
→ Not quite. That's the size in bytes, before dividing by the size of one element.
````

````quiz
What is the value of `values[3]` after `int values[5] = {1, 2, 3};`?
○ 3
→ Not quite. The third value is at index 2, and index 3 has no value listed.
◉ 0
→ Yes. Elements without a listed value are set to zero.
○ It can't be read, because it wasn't listed.
→ Not quite. It can be read, and it's zero.
````
