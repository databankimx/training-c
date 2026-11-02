## Strings and pointers

The arrays chapter showed a string as an array of characters, and the strings chapter used it that way. A string is also a pointer to its first character, and most C code passes strings around in exactly that form. This step puts the two views together.

Here's the program for this step, in `src/main.c`:

```c
const char *food = "Pizza";
printf("%s\n", food);
printf("First: %c\n", *food);
printf("Third: %c\n", food[2]);
printf("Length: %zu\n", strlen(food));
```

Press **Run**. The output is:

```
Pizza
First: P
Third: z
Length: 5
```

The string literal `"Pizza"` is stored as an array of six characters, the five letters and the zero byte. When it's used as a value, the array becomes a pointer to its first character, which is why `food` can be assigned from the literal with no operator. `*food` reads that first character, `P`, and `food[2]` reads the third, `z`. Because `food` points at the first character, `%s` prints everything from there up to the zero byte.

`strlen` takes a pointer. It starts at the address it's given, and counts characters until it reaches the zero byte, so it works on any string, whether it's an array or a pointer.

### const char *

The declaration is `const char *food`, and the `const` matters. A string literal can't be changed. Writing through a pointer to it is undefined behavior, and many compilers refuse the program outright. Adding `const` makes the rule explicit: the pointer can point at a different string, but the characters it points at can't be changed through it.

Most string parameters and string variables in C are declared `const char *` for this reason, when the function or variable only reads the text.

### char name[] versus const char *

These two declarations look alike, and they behave differently:

```c
char name[] = "Ada";
const char *title = "Ada";
```

`name` is an array. It holds its own copy of the characters, in memory the program can write to. The `copy` in this step shows that: `char *copy = name;` points at the array's first character, and `copy[0] = 'E';` changes the array, so the name is now `Eda`.

`title` is a pointer. It points at the string literal, which has no room to change, so writing through `title` is an error. Use the array form when the program needs to change the text, and the pointer form when it only needs to read it.

### An array of strings

An array of strings is an array of pointers, one per string:

```c
const char *colors[3] = {"red", "green", "blue"};
for (size_t i = 0; i < 3; i++) {
    printf("%s\n", colors[i]);
}
```

The output is `red`, `green`, and `blue`, each on its own line. Each element of `colors` is a `const char *`, so `colors[i]` is one pointer, and `%s` prints the string it points at. This is the form the weekday homework in Chapter 4 approximated with a two-dimensional character array. The array of pointers is more flexible, because each string can have a different length, and the rows don't need to be padded to the longest one.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `*food` give, for `const char *food = "Pizza";`?
○ The whole string, "Pizza".
→ Not quite. A single star reads one character, the one at the start of the string.
◉ The character 'P'.
→ Yes. The star reads the first character the pointer refers to.
○ The address of the string.
→ Not quite. The address is what food holds. The star gives the character at that address.
````

````quiz
Which declaration gives a string that the program can change?
○ const char *name = "Ada";
→ Not quite. A pointer to a string literal can't be changed through, and the const says so.
◉ char name[] = "Ada";
→ Yes. An array holds its own copy of the characters, which the program can write to.
○ char *name = "Ada";
→ Not quite. This points at the literal, and writing through it is undefined behavior.
````

---

### Try it in the runner

Change `food` to point at `"Salad"`, and predict the `Third:` line before you press **Run**. The third character of `Salad` is `l`, so the line reads `Third: l`. Then predict the `Length:` line for `"Salad"`: it's 5 again.

Then try to change a character through `food`, by adding `food[0] = 'p';`. The compiler refuses it, because `food` is a `const char *`. Remove the line before you continue.

---

A string is an array of characters, and when a program passes it around, the program passes a pointer to its first character. The `const` in `const char *` says the text is only read, and an array holds its own text, which can be changed.
