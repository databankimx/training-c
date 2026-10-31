## Battleship

This step puts the chapter together in one program: a two-dimensional array holds the state of the game, a `while` loop keeps the game going, and `if` and `else` decide what each move does. It's also the first program in the course that plays against the person using it.

Here's the grid, from the top of `src/main.c`:

```c
int ships[4][4] = {
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0}
};
```

A `1` marks a square with a ship, and a `0` marks water. The grid has four ship squares: row 0 has ships at columns 1 and 2, and column 2 has ships at rows 2 and 3. The game ends when all four have been hit.

Press **Run**. The Output pane asks for a row, then a column. Each answer is typed into the input box, and Enter sends it. The program then reports a hit or a miss, and asks again.

### The game loop

The game is a `while` loop, which runs while there are ships left:

```c
while (hits < 4) {
    /* ask for a row and column, then check the square */
}
```

Each pass asks for a move, checks the grid, and updates the count of hits. `hits` starts at 0, and the loop ends once it reaches 4. The `turns` counter goes up on every valid move, so it can report the score at the end.

### Checking the square

Once the program has a row and a column, it looks up that square with two indexes:

```c
if (ships[row][column] == 1) {
    ships[row][column] = 0;
    hits++;
    printf("Hit! %d left.\n\n", 4 - hits);
} else {
    printf("Miss\n\n");
}
```

A hit sets the square to 0, so the same square can't count twice. Setting it to 0 is how the program remembers the hit. The message reports how many ships are left, which is `4 - hits`, since four ships start the game.

Notice that the grid is the only record of which squares have been hit. The program doesn't need a separate list of ships. The array's contents are the game state, and changing an element changes the game.

### Checking the input

The program checks the row and column before it uses them as indexes:

```c
if (row < 0 || row > 3 || column < 0 || column > 3) {
    printf("Please choose numbers from 0 to 3.\n\n");
    continue;
}
```

Without this check, a row of 4 would read past the end of the grid, which is undefined. The `continue` skips the rest of the pass, so the bad move doesn't count as a turn, and the loop asks again. The same use of `continue` as in the break and continue step, and the same reason for it, applies here.

Checking the range is not enough on its own, because the text the player types may not be a number at all. `fgets` reads the whole line, and `strtol` converts it, but `strtol` returns 0 for text it can't read, which is a legal row. The program needs a way to tell "the player typed 0" from "the player typed no number", and the second pointer argument to `strtol` gives it one:

```c
char *row_end = line;
long row = strtol(line, &row_end, 10);
if (row_end == line) {
    printf("Please type a number.\n\n");
    continue;
}
```

`strtol` sets `row_end` to point at the first character it didn't read. If it read nothing, `row_end` still points at the start of the text, which is the same address as `line`. That's the test. The expression `&row_end` passes the address of the pointer itself, so `strtol` can change where it points, which the pointers chapter covers.

C++ streams handle bad input differently, and the C++ version of this lesson describes a failed stream that must be reset and cleared before the next read. C doesn't have that state. `fgets` always consumes the whole line, so a bad entry can't repeat itself on the next read. What C does need is the explicit check above, because `strtol` reports failure only through the end pointer.

### Quitting

The player needs a way out that doesn't depend on the **Stop** button. The program checks the first character of each answer, before it tries to read a number:

```c
if (line[0] == 'q' || line[0] == 'Q') {
    break;
}
```

If the first character is `q`, the `break` leaves the loop, and the game ends with a message about the ships left. The check accepts `Q` too.

The quit check only looks at the first character, so `quit` also ends the game. Everything after the `q` is ignored, because the program leaves the loop and doesn't read again.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does the game set a hit square to 0?
○ To hide the square from the player.
→ Not quite. The player is never shown the grid, so hiding it isn't the issue.
◉ So the same square can't count as a hit twice.
→ Yes. The grid records which squares still have ships.
○ Because 0 is the default value of an array.
→ Not quite. That's true, but it isn't why the program sets the value.
````

````quiz
A player enters row 4. What does the `continue` in the check do?
○ It ends the game.
→ Not quite. continue doesn't end the loop.
◉ It skips the rest of this pass, so the move isn't counted and the loop asks again.
→ Yes. The bad move doesn't reach the grid, and the loop goes around again.
○ It counts the move as a miss.
→ Not quite. A rejected move isn't checked against the grid at all.
````

---

### Try it in the runner

Type `x` at the row prompt, and check that the program says it needs a number and asks again, rather than repeating forever. Then type `q` at the column prompt, and check that the game ends with the quit message. Then play a game, and count the hits. Each square with a 1 is a hit, and the game ends after four. Then change a `1` in the grid to a `0`, and predict whether the game still ends after four hits. It doesn't: there are only three ships now, so the loop can't reach four hits, and the player has to type `q` to leave.

Then change `hits < 4` to `hits < 3`, and predict how the game ends. It stops after three hits, while a ship is still on the grid. The final message reports one ship left, which is correct for the count, but the game ended early. The loop's condition and the grid have to agree.

---

Battleship uses every idea in this chapter: the two-dimensional array holds the state, the loop keeps the game going, and the checks decide each move. The summary covers the chapter's loops together, and the homework practices them on their own.
