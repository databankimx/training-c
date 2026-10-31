## Summary: Decisions

This chapter covered how a program chooses what to do, based on the values it has.

* **`bool` holds true or false.** It's stored as an integer, so `printf` with `%d` prints 1 and 0. A conditional, `? "true" : "false"`, prints the words.
* **Comparisons ask questions.** `==`, `!=`, `<`, `>`, `<=`, and `>=` each give a bool. Equality is `==`, and a single `=` assigns a value instead.
* **Logical operators combine bools.** `&&` needs both sides to be true, `||` needs one, and `!` flips a value. XOR is true when exactly one side is true, and C doesn't have a logical XOR operator, so it's written as `p != q`, or as `(p || q) && !(p && q)`.
* **Precedence sets the reading order.** `!` binds most tightly, then the comparisons, then `==` and `!=`, then `&&`, then `||`. Add parentheses when mixing `&&` and `||`, and GCC's warning will not appear.
* **Short-circuit evaluation stops early.** `&&` and `||` skip the right side when the left side already decides the answer. Put the safe check first.
* **`if` runs a block on a condition.** `else` runs when the condition is false, and `else if` tests further conditions in order. The first true branch wins. The final `else` is optional.
* **Chain or separate `if` blocks.** A chain runs only one block, so use it when the conditions exclude each other. When several conditions can apply, and each should run, use separate `if` blocks.
* **The conditional operator chooses a value.** `condition ? a : b` gives `a` when the condition is true, and `b` otherwise.
* **`switch` picks a case by value.** Use it when one value is compared with several constants. Each case ends with `break`, unless a `/* fall through */` comment marks the drop-through as deliberate. A `switch` works on integers and `char`, not on strings.
* **Always use braces.** They stop a later edit from putting a line outside the `if` by accident.

### Check your understanding

*These questions are written for this course.*

````quiz
What does `printf` print for a bool holding true, when the format is `%d`?
○ true
→ Not quite. %d prints the number, not the word.
◉ 1
→ Yes. A bool is stored as an integer, so true is 1.
○ 0
→ Not quite. That's the value of false.
````

````quiz
Which expression is true when `age` is 15 and `has_permission` is true?
○ age >= 18 && has_permission
→ Not quite. 15 is not 18 or over, so the left side is false.
◉ age < 18 || has_permission
→ Yes. Either side being true is enough for ||, and has_permission is true.
○ age == 15 && !has_permission
→ Not quite. That needs has_permission to be false, and it's true here.
````

````quiz
What is the value of `result` after `int result = (5 > 3) ? 10 : 20;`?
○ 20
→ Not quite. 20 is the value used when the condition is false, and 5 is greater than 3.
◉ 10
→ Yes. The condition is true, so the first value, 10, is used.
○ true
→ Not quite. The conditional operator gives one of its two values, not the condition itself.
````
