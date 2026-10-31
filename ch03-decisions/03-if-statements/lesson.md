## If statements

So far, every program has run from top to bottom, with each line happening once. An `if` statement lets the program choose between paths. It checks a condition, and runs one block of code when the condition is true, and another when it's false. That's the step where your programs start to respond to the values they're given.

Here's the program for this step, in `src/main.c`. It begins with a plain `if`:

```c
int x = 20;
int y = 10;

if (x > y) {
    printf("x is greater than y\n");
}
```

The condition goes in parentheses, and the code to run goes in curly braces. If the condition is true, the block runs. If it's false, the block is skipped, and the program carries on after the closing brace.

The program has three of these in a row: one for `x == y`, one for `x > y`, and one for `x < y`. Each one stands alone, so the program tests all three, whatever the others found. With `x` at 20 and `y` at 10, only the middle one is true, so that's the only message that appears:

```
x is greater than y
```

Note the `==` in the first test. A single `=` assigns a value, and a condition written with `=` is almost always a bug. The chapter on booleans covered this, and it's the most common mistake with `if`.

### if and else

Often you want one of two things to happen, depending on the answer. That's what `else` is for:

```c
int age = 16;
int voting_age = 18;
if (age >= voting_age) {
    printf("You can vote!\n");
} else {
    int wait = voting_age - age;
    printf("You will be able to vote in %d years.\n", wait);
}
```

The output is:

```
You will be able to vote in 2 years.
```

The `else` block runs only when the condition is false, so exactly one of the two messages is printed. Notice that `wait` is declared inside the `else` block. A variable declared inside braces exists only until the closing brace, which keeps names from leaking into the rest of the program.

### else if

When there are more than two possibilities, `else if` lets you test each one in turn:

```c
int driver_age = 20;
if (driver_age >= 21) {
    printf("You drive, vote, and rent a car.\n");
} else if (driver_age >= 18) {
    printf("You can drive and vote, but you can't rent a car.\n");
} else if (driver_age >= 16) {
    printf("You can drive, but you can't vote or rent a car.\n");
} else {
    printf("You can't drive, vote, or rent a car.\n");
}
```

The conditions are checked from the top down, and the first one that's true wins. Once a block has run, the rest of the chain is skipped. That's why the conditions go from the most specific to the least. With `driver_age` at 20, the first test fails, the second passes, and the rest are ignored.

The output is:

```
You can drive and vote, but you can't rent a car.
```

### Leaving out the final else

The `else` at the end of a chain is optional. Leave it out when nothing needs to happen if none of the conditions match. The score example in the program does exactly that:

```c
int score = 75;
if (score >= 90) {
    printf("Excellent\n");
} else if (score >= 70) {
    printf("Good\n");
}
```

With a score of 75, the output is `Good`. With a score of 50, neither condition is true, there's no `else` to catch it, and the program prints nothing. That's correct here, because the program has no message to give a low score. Add an `else` only when there's something to do in that case.

A chain can also have any number of `else if` blocks with no `else` at all. The rule is the same: the first true condition runs, and if none is true, nothing runs.

### Chained or independent?

The chain has one important property: only one of its blocks ever runs. The next example shows why that matters, because it's easy to pick the wrong structure. A store gives a bulk discount for more than 10 items, and free shipping for more than 5:

```c
int items = 12;
if (items > 10) {
    printf("Chained: bulk discount\n");
} else if (items > 5) {
    printf("Chained: free shipping\n");
}
```

The output is:

```
Chained: bulk discount
```

The customer with 12 items should get both, but the chain stops after the first match, so free shipping is never checked. The program now uses two separate `if` blocks instead:

```c
if (items > 10) {
    printf("Independent: bulk discount\n");
}
if (items > 5) {
    printf("Independent: free shipping\n");
}
```

The output is:

```
Independent: bulk discount
Independent: free shipping
```

Each `if` is checked on its own, whatever the others found. That's the right choice when the conditions don't exclude each other, and more than one should apply.

The question to ask is simple: can two of these conditions be true at once, and should both blocks run when they are? If the answer is no, use a chain, because the chain makes that rule explicit. If the answer is yes, use separate `if` blocks. The first `if` in this step's program, with its three checks on `x` and `y`, is a different case. Those conditions exclude each other, since only one can be true, so a chain would work just as well there. The separate `if` blocks are a style choice, and the chain is the more explicit of the two.

### The conditional operator

For a simple choice between two values, the conditional operator is shorter:

```c
const char *size = (x > y) ? "large" : "small";
printf("Size: %s\n", size);
```

The question mark sits between the condition and the first value, and the colon separates the two values. If the condition is true, the first value is used. Otherwise, the second is. It's the same as an `if` with an `else`, written as one expression, so it works well for choosing a value rather than running several lines of code.

The output is:

```
Size: large
```

### Use braces every time

C lets you leave the braces off when a block has only one statement. Don't do it. Without braces, a later edit that adds a second line can end up outside the `if` without any warning, and the bug is hard to spot. Put braces on every `if`, `else`, and `else if`, even for one line.

---

### Quiz

*These questions are written for this course.*

````quiz
Which block runs when the condition in an `if` is false?
○ The if block.
→ Not quite. The if block only runs when the condition is true.
◉ The else block, if there is one.
→ Yes. If there's no else, nothing runs, and the program carries on after the if.
○ Both blocks.
→ Not quite. Exactly one block runs in an if and else pair.
````

````quiz
In an `else if` chain with `age` equal to 19, and tests of `age >= 21`, then `age >= 18`, then `age >= 16`, which branch runs?
○ The first branch, for age 21 or over.
→ Not quite. 19 is not 21 or over.
◉ The second branch, for age 18 or over.
→ Yes. The first test fails, and the second is the first one that's true.
○ All three branches.
→ Not quite. Once a branch runs, the rest of the chain is skipped.
````

````quiz
An order has 12 items, and both a bulk discount and free shipping should apply. Which structure prints both messages?
○ An else if chain.
→ Not quite. Once the first branch runs, the rest of the chain is skipped, so only one message prints.
◉ Two separate if blocks.
→ Yes. Each if is checked on its own, so both can run.
○ An if with an else.
→ Not quite. An else only runs when the if is false, so it can't add a second message here.
````

---

### Try it in the runner

Change `driver_age` to `17`, and press **Run**. Before you do, work out which message prints. Seventeen is not 21 or over, and not 18 or over, but it is 16 or over, so the third message prints: `You can drive, but you can't vote or rent a car.`

Then change `x` to `10`, so `x` and `y` are equal, and predict which of the first three messages print. Only the first one checks for equality, and the other two compare with `>` and `<`, so only the first prints, and the other two are skipped.

---

With `if`, a program can respond to its data. The summary and the homework put these decisions together, so you can write small programs that make choices for themselves.
