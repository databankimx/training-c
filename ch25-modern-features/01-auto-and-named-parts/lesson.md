## auto and named parts

Modern code removes much of the repetition that older code needed. C23, the newest C standard, adds `auto`, which lets the compiler work out a variable's type from the value it's given, as C++ does. The type is still fixed at compile time, and any later use that doesn't fit it is an error.

C23 `auto` is declared with the standard's `-std=c23` mode, which this chapter's CMake file sets. Here's the part of `src/main.c` that uses it:

```c
auto total = 3;
auto average = 4.5;
printf("%d %g\n", total, average);
```

`total` is an `int`, and `average` is a `double`. The compiler takes each type from the initializer. The format string has to match, since `printf` doesn't check the types of its arguments against the conversions in the format, so the `%d` and `%g` are the programmer's promise.

Press **Run**. The output is:

```
Ada: 91
Grace: 88
3 4.5
```

### Named parts instead of structured bindings

The C++ lesson unpacks a map element with a structured binding, `[name, score]`. C has no such syntax. The C version uses a structure with named members, and reads each part by its name:

```c
typedef struct {
    const char *name;
    int score;
} Score;

const Score *entry = &scores[i];
printf("%s: %d\n", entry->name, entry->score);
```

The names are the same ones the binding would have used, and the pointer avoids a copy of each record. The C form is one line longer, and it states each member name in full, which is the readability the binding gave.

### Order is the programmer's job

C has no map, so the scores are kept in an array, and the array's order is the one it was written in. The C++ map sorted its keys, so Ada came before Grace whatever the order of insertion. An array doesn't do that. If the output must be in name order, the program has to sort it, which the sorting chapter covers, or the data has to be written in that order.

### Where auto helps

`auto` is most useful when the type is long to write, or when a change to one type should flow through the code without edits. It should not hide a type that a reader needs to see, such as a value whose meaning depends on its width. Use it where the initializer makes the type obvious, and write the type out where it isn't.

---

### Quiz

*These questions are written for this course.*

````quiz
What type does `auto total = 3;` give `total` in C23?
○ A type chosen at run time, from the value.
→ Not quite. The type is fixed at compile time.
◉ int, taken from the initializer 3, and fixed for the rest of the program.
→ Yes. auto takes the type from the initializer, and it never changes.
○ long, since the standard requires it.
→ Not quite. The type comes from the initializer, and 3 is an int.
````

````quiz
Why does the C version keep the scores in name order by hand?
○ Because C arrays cannot hold structures.
→ Not quite. Arrays of structures are ordinary C.
◉ Because C has no map that sorts its keys, so the order is whatever the program writes.
→ Yes. The array keeps the order it was written in, and nothing sorts it.
○ Because auto requires sorted input.
→ Not quite. auto works on any initializer, sorted or not.
````

---

### Try it in the runner

Add `{"Linus", 95}` to the end of the array, and predict the order of the output lines before you press **Run**. Linus comes last, after Grace, since the array keeps the order it was written in. A map would have sorted him in the same position here, but only because his name sorts after the others, and the C array would keep that order even if he were added first.

---

`auto` gives C23 code the short declarations that C++ code has, and named members stand in for structured bindings. The next step covers optional values, where C needs a struct to say that a result may be missing.
