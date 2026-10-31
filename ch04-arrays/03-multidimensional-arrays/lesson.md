## Multidimensional arrays

A list is a one-dimensional array: each element has one index. Many real things are two-dimensional. A grid of cells, a seating plan, or the squares of a board each need a row and a column. C arrays can have more than one index, and the form is the same as before, with another pair of square brackets.

Here's the program for this step, in `src/main.c`. It begins with a 2 by 4 grid of characters:

```c
char letters[2][4] = {
    {'A', 'B', 'C', 'D'},
    {'E', 'F', 'G', 'H'}
};

printf("%c\n", letters[1][2]);
printf("%c\n", letters[0][3]);
```

Press **Run**. The output is:

```
G
D
```

The declaration `letters[2][4]` means two rows, each with four columns. The braces follow the same layout: the outer braces hold the rows, and each inner pair of braces holds one row's values, in order. The example uses single characters rather than strings, because a string in C is itself an array, and a two-dimensional array of strings would need each row to be padded to the longest name. Characters keep the grid simple. The first step of this chapter shows the pointer form of an array of strings, which doesn't need padding.

The first index picks the row, and the second picks the column. Both start at zero. So `letters[1][2]` is row 1, column 2, which is `G`, and `letters[0][3]` is row 0, column 3, which is `D`. Read the two indexes in the order they're written, row first.

### A grid of numbers

The program then works with a 3 by 3 grid of integers:

```c
int grid[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
printf("Center: %d\n", grid[1][1]);
printf("Sum of the first row: %d\n", grid[0][0] + grid[0][1] + grid[0][2]);
```

The output is:

```
Center: 5
Sum of the first row: 6
```

`grid[1][1]` is the middle of the grid, 5. The row sum adds the three values in row 0. Each element is an ordinary `int`, so you can read it, change it, and use it in arithmetic, exactly as you would a single-dimension element.

Changing one element works the same way:

```c
grid[2][0] = 0;
printf("Bottom-left: %d\n", grid[2][0]);
```

The output is `Bottom-left: 0`.

### Checking the bounds

Every index has its own limit. In `letters[2][4]`, the row index can be 0 or 1, and the column index can be 0 to 3. Using `letters[2][0]` or `letters[0][4]` is outside the array, and the result is undefined, just as with a one-dimensional array. C doesn't check either index. Check both when you're unsure, since a bad row index is as dangerous as a bad column index.

### More dimensions

C allows more than two dimensions, such as `int cube[2][2][2]`, which has an index for depth as well. The rule doesn't change: each index counts from zero and must stay within its own size. In practice, two dimensions covers most of what you'll meet early on, so this course stops there.

---

### Quiz

*These questions are written for this course.*

````quiz
In `int grid[3][5]`, how many elements does the array hold?
○ 8
→ Not quite. That's the sum of the sizes, not the number of elements.
◉ 15
→ Yes. Three rows of five columns gives 15 elements.
○ 5
→ Not quite. That's the number of columns in each row.
````

````quiz
Which index pair refers to the element in row 1, column 0 of `letters[2][4]`?
○ letters[0][1]
→ Not quite. That's row 0, column 1, which is in the first row.
◉ letters[1][0]
→ Yes. The first index is the row, and the second is the column.
○ letters[0][1][1]
→ Not quite. letters is two-dimensional, so it takes two indexes.
````

---

### Try it in the runner

Predict the value of `grid[1][2]` before you press **Run**. Row 1 is `{4, 5, 6}`, so the answer is 6. Then change it to `grid[2][2]`, and predict again. That's the bottom-right corner, which is 9.

Then change the index to `grid[3][0]`, and predict what happens. The grid has three rows, so row 3 doesn't exist. As with any out-of-bounds index, the result is undefined, and the program won't tell you about it.

---

Two-dimensional arrays model grids, and they're the natural shape for a board game. The loops chapter covers how you visit every cell of a grid without writing out each index, and the Battleship example uses that to play a whole game.
