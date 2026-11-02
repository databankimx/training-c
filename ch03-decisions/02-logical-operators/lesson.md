## Logical operators and short-circuiting

Comparison operators answer one question. Logical operators combine questions, or choose between values. They also short-circuit: C stops evaluating as soon as the result is already known.

Here's the start of the program for this step, in `src/main.c`:

```c
bool x = true;
bool y = false;

printf("x && y: %s\n", (x && y) ? "true" : "false");
printf("x || y: %s\n", (x || y) ? "true" : "false");
printf("!x: %s\n", !x ? "true" : "false");
```

Press **Run**. The output is:

```
x && y: false
x || y: true
!x: false
```

`&&` means "and". The result needs both sides to be true.

`||` means "or". The result is true when at least one side is true.

`!` means "not". It reverses its operand, so true becomes false and false becomes true.

C prints a `bool` as the number 1 or 0, so the program uses a conditional, `? "true" : "false"`, to print the words. The conditional picks the text that matches the value.

### Truth tables

The two-input operators are easier to predict when every combination is laid out. In each table, `t` means true and `f` means false for the inputs, and `T` and `F` show the result. The runner colors the results, so they're easy to scan.

For `&&`, the result is true only when both inputs are true:

| p | && | q |
| - | - | - |
| t | T | t |
| t | F | f |
| f | F | t |
| f | F | f |

For `||`, the result is true when at least one input is true. A single true input is enough:

| p | \|\| | q |
| - | - | - |
| t | T | t |
| t | T | f |
| f | T | t |
| f | F | f |

Negation has one input. `!` reverses it:

| p | !p |
| - | - |
| t | F |
| f | T |

Read the tables as a checklist. When you're unsure what an expression gives, find the row for its inputs and read off the result.

### Combining comparisons

The operators become useful when they join comparisons, as the next lines of the program do:

```c
int age = 25;
bool has_ticket = false;
printf("Adult and has ticket: %s\n", (age >= 18 && has_ticket) ? "true" : "false");
printf("Adult or has ticket: %s\n", (age >= 18 || has_ticket) ? "true" : "false");
```

The output is:

```
Adult and has ticket: false
Adult or has ticket: true
```

`age >= 18` is true, and `has_ticket` is false. So `&&` is false, because the person hasn't got a ticket, and `||` is true, because being an adult is enough for an OR. Each side of an operator is a full expression, so the comparison doesn't need extra parentheses around it.

### Short-circuit evaluation

The next part of the program is where the operators stop early:

```c
int count = 0;
bool ok = (count != 0) && (10 / count > 1);
```

Dividing by zero is a serious error in C, so this line needs care. It works because `&&` stops as soon as the answer is known. The left side, `count != 0`, is false, so `&&` can't be true, and the right side is never evaluated. The division never happens.

The same applies to `||` in the other direction. If the left side is true, the right side is skipped, because an OR is already true.

This is called short-circuit evaluation. It's the reason to put the cheap or safe check first. The arrays chapter will use the same idea to check an index before reading an array element.

### XOR

XOR means "exclusive or". The result is true when exactly one input is true, and false when both are true or both are false. In everyday terms, it's "one or the other, but not both". A light switch controlled from two places works this way, and so does a yes-or-no choice with exactly one correct answer.

Here's the table for XOR:

| p | XOR | q |
| - | - | - |
| t | F | t |
| t | T | f |
| f | T | t |
| f | F | f |

C doesn't have a logical XOR operator, so we build one from the operators we already have. The program shows two ways:

```c
bool p = true;
bool q = false;

bool my_xor = (p || q) && !(p && q); // example explaining the logic
printf("(p || q) && !(p && q): %s\n", my_xor ? "true" : "false");

my_xor = p != q; // simple example with less obvious logic
printf("p != q: %s\n", my_xor ? "true" : "false");
```

The output is:

```
(p || q) && !(p && q): true
p != q: true
```

The first form, `(p || q) && !(p && q)`, spells the logic out. The first half, `p || q`, needs at least one true input. The second half, `!(p && q)`, rules out the case where both are true. Together, they're true only when exactly one input is true. It's longer, but each part maps directly onto the definition, which makes it the version to read when you're learning what XOR means.

The second form, `p != q`, is shorter, and its logic is less obvious at first glance. Two bool values are different exactly when one is true and the other is false, which is XOR by definition. Once you see that, it's the one most programmers would write. It's worth checking it against the table to convince yourself.

Both forms give the same result for every combination in the table, so choose whichever reads more clearly to the person who will maintain the code.

C does have a bitwise XOR operator, `^`. On values that are only 0 or 1, it gives the same answer as the logical XOR above. It works on any integer bit by bit, so it's a different tool for the job, and the bitwise operators are a topic for a later chapter.

---

### Precedence and grouping

When an expression has several operators, C decides the order in which they run. That order is called precedence, and it decides how an expression is read:

```c
true || false && false
```

Without any rules, you might read it left to right, giving `(true || false) && false`, which is false. C reads it differently. `&&` binds more tightly than `||`, so the `&&` is worked out first, and the expression is `true || (false && false)`, which is true.

These are the precedence rules for the operators in this lesson, from the tightest binding to the loosest:

| Level | Operators | Notes |
| - | - | - |
| 1 | `!` | Applies to the value directly after it. |
| 2 | `<`, `<=`, `>`, `>=` | Comparisons. |
| 3 | `==`, `!=` | Equality comparisons. |
| 4 | `&&` | Logical AND. |
| 5 | `\|\|` | Logical OR. |

Some results follow directly from the table. `!p && q` is `(!p) && q`, because `!` binds more tightly. `age >= 18 && has_ticket` is `(age >= 18) && has_ticket`, because the comparison binds more tightly than `&&`. And `p != q && r` is `(p != q) && r`, because `!=` binds more tightly than `&&`.

Mixing `&&` and `||` without parentheses is so easy to misread that GCC warns about it. The example above, `true || false && false`, is in this lesson's text only, and not in the program. With `-Wall` on, GCC reports it under `-Wparentheses`, and this course keeps every step free of warnings. The fix is to add parentheses, which is what a program should do with `(true || false) && false`.

The rule of thumb is simple: when you combine `&&` and `||`, add parentheses. Parentheses cost nothing, and they tell the next reader what you meant.

---

### Quiz

*These questions are written for this course.*

````quiz
Using the truth table, when is `p || q` false?
○ When p is true.
→ Not quite. When p is true, the result of || is always true.
◉ When both p and q are false.
→ Yes. || needs at least one true input, so both being false gives false.
○ When both p and q are true.
→ Not quite. That gives true for ||.
````

````quiz
Which expression is true when `p` and `q` are both true?
○ p != q
→ Not quite. Two equal bools are not different, so p != q is false here.
◉ !(p != q)
→ Yes. p != q is false when both are true, so its negation is true.
○ p && !q
→ Not quite. q is true, so !q is false, and the whole expression is false.
````

````quiz
What does `true || false && false` give in C?
○ false, because it's read left to right.
→ Not quite. && binds more tightly than ||, so it isn't read left to right.
◉ true, because the && is worked out first.
→ Yes. The expression is true || (false && false), which is true.
○ Syntax error, because mixing || and && is not allowed.
→ Not quite. It compiles, but GCC warns about it, which is why we add parentheses.
````

---

### Try it in the runner

Change `p` and `q` to both be `true`, and press **Run**. Predict both XOR results before you do. Both should now be false, because two equal values are not different, and exactly one input is not true.

Then change `(p || q) && !(p && q)` to `(p || q) && (p && q)`, and predict the result for the original values, `p` true and `q` false. The answer is false, because the second half is now `p && q`, which is false when `q` is false. It's a different rule, and the table shows why.

---

## More background

See the [Wikibooks C Programming book](https://en.wikibooks.org/wiki/C_Programming), which this course draws on. Its operator sections cover the same ideas in more depth.

---
