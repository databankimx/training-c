## Summary: Loops

This chapter covered how a program repeats work, and how to control a loop while it runs.

* **`while` checks first.** The condition is tested before each pass, so the block may never run.
* **`do-while` checks last.** The block always runs once, and the condition is tested after it. Note the semicolon after its closing parenthesis.
* **`for` keeps the counter together.** The start, the condition, and the step sit on one line at the top of the loop.
* **An index loop visits each element.** `for (size_t i = 0; i < count; i++)` runs the body once for each position, and `sizeof` gives the count when the array's declaration is in view.
* **`break` stops the loop.** The program continues after the loop's closing brace.
* **`continue` skips to the next pass.** The step of a `for` loop still runs before the next check.
* **`break` and `continue` apply to the innermost loop.** In nested loops, they don't affect the outer one.
* **Make sure the loop can end.** A `while (true)` loop needs a `break`, and a `while` loop needs a change to its condition inside the body.
* **A game is a loop around a state.** Battleship keeps its state in a two-dimensional array, and a `while` loop runs until the game is won.
* **Check text before you use it as a number.** `strtol` reports failure only through its end pointer, so compare that pointer with the start of the text.

### Check your understanding

*These questions are written for this course.*

````quiz
Which loop should you use to run a block at least once, before the condition is checked?
○ while
→ Not quite. A while loop checks the condition first, so its block can be skipped.
◉ do-while
→ Yes. The block runs first, and then the condition is checked.
○ for
→ Not quite. A for loop checks its condition before each pass, like a while loop.
````

````quiz
What does this loop print?
`for (int i = 1; i <= 6; ++i) { if (i % 2 == 0) { continue; } printf("%d ", i); }`
○ 2 4 6
→ Not quite. continue skips the even numbers, so they don't print.
◉ 1 3 5
→ Yes. The odd numbers are printed, and the even ones are skipped.
○ 1 2 3 4 5 6
→ Not quite. The continue skips the even numbers before the printf line.
````

````quiz
In nested loops, what does a `break` in the inner loop do?
○ It ends the whole program.
→ Not quite. A break ends a loop, not the program.
◉ It ends only the inner loop, and the outer loop carries on.
→ Yes. A break applies to the innermost loop it sits in.
○ It ends the outer loop as well.
→ Not quite. The outer loop carries on with its next pass.
````
