## Strings

Numbers aren't the only thing programs work with. Names, messages, file paths, and the text a user types are all strings. In C, a string is an array of `char` values that ends with a zero byte, and the string functions come from `<string.h>`. You've already seen one: the name in the input step was a string.

This is an introduction, so we'll keep it to the basics you'll need in the next step and the homework. We come back to strings in more depth later in the course, where we look at searching, splitting, and the rules for working with text safely.

Here's the program for this step, in `src/main.c`. It starts with a name, and then builds a greeting:

```c
char name[] = "Ada Lovelace";
printf("Name: %s\n", name);
printf("Length: %zu\n", strlen(name));
printf("Bytes stored: %zu\n", sizeof name);
printf("First letter: %c\n", name[0]);
printf("Same as \"Ada\"? %s\n", strcmp(name, "Ada") == 0 ? "yes" : "no");
```

Press **Run**. The first five lines of output are:

```
Name: Ada Lovelace
Length: 12
Bytes stored: 13
First letter: A
Same as "Ada"? no
```

The greeting is built in the second half of the program, and its output is:

```
Hello, C!
Length: 9
First letter: H
Hello, C! Welcome.
Tab:	Backslash:\ Quote:"
```

The `Tab:` line contains a real tab character, which is why the gap appears in the output. Each part of the program is explained below.

### Format specifiers

The program uses `printf` with several placeholders. Each one starts with `%` and says what kind of value goes in that spot:

| Specifier | Type it's for | Used in this program | Example output |
|---|---|---|---|
| `%s` | A string, which is a char array ending in a zero byte | `Name: %s` | `Name: Ada Lovelace` |
| `%zu` | A `size_t`, the type `strlen` and `sizeof` return | `Length: %zu` | `Length: 12` |
| `%c` | A single `char` | `First letter: %c` | `First letter: A` |

The specifier must match the type of the value. `%s` given a `char` instead of a string prints garbage, and `%d` given a string prints a meaningless number. A value of the wrong type can crash the program, so match them carefully.

Two more are worth knowing. `%%` prints a single percent sign. `%.2f` prints a `double` with two digits after the point, as the arithmetic lesson used.

### Quotes matter

Double quotes make a string, as in `"Hello"`. Single quotes make a single character, as in `'H'`. The two are different types, so `"H"` and `'H'` aren't interchangeable. The string `"H"` is an array of two characters, the letter and the zero byte, and the character `'H'` is one `char`. Passing one where the other is expected gives a warning or an error, so read the message when you see one.

### Length and size are different

`strlen` counts the characters before the zero byte, so `Ada Lovelace` has a length of 12. `sizeof name` is the size of the whole array, which is 13, because the zero byte takes a place too. Confusing the two is one of the most common sources of bugs in C text code: an array sized from the length, with no room for the zero, can't hold the string it was meant to.

### Strings are arrays

`name[0]` is the first character, `A`, and `name[11]` is the last, `e`. Indexing starts at 0, as it did for arrays in the arrays chapter. The first character is at position 0, the second at 1, and so on. This is the most common source of off-by-one mistakes, and you'll meet it again.

The same is true of the greeting. `greeting[0]` is `H`, and the program prints `First letter: H`.

### Joining text

Here is a difference from many other languages. In C, `+` doesn't join strings. `"Hello" + "C"` tries to add two addresses, which is meaningless. To build a string from pieces, use `snprintf`, which writes formatted text into an array:

```c
char greeting[64];
snprintf(greeting, sizeof greeting, "%s, %s!", "Hello", "C");
```

The first argument is the array to write into, the second is its size, and the rest is a format string, just like `printf`. The size stops `snprintf` before it overflows the array, which is why the program passes `sizeof greeting` and not a number. The output is `Hello, C!`, and the length is 9.

The array has to be big enough for the whole result, including the zero byte. The program uses 64 characters, which is plenty for a short greeting. Picking a size you can't be sure of, without checking, is the kind of decision that causes overflows.

### Adding to a string

`strcat` adds text to the end of a string, which is what `+=` does for a string in other languages:

```c
strcat(greeting, " Welcome.");
```

Now `greeting` holds `Hello, C! Welcome.`, and its length is 18. `strcat` changes the array itself, and it doesn't check the size either. The destination must be large enough for both pieces together, or it writes past the end.

### Comparing strings

`==` compares the addresses of two arrays, not their text, so `name == "Ada"` is not the test you want. `strcmp` compares the text. It returns 0 when the two strings are equal, which is why the program writes `strcmp(name, "Ada") == 0`.

### Copying and the length trap

`strcpy` copies text into an array, but it doesn't check that the array is big enough. If the text is longer, it writes past the end of the array, which is a buffer overflow, a common cause of security problems. Use `strncpy` or `snprintf`, which take the array's size and stop before it overflows, and always check that the destination is large enough for the text.

### Special characters

A string can't contain a double quote directly, because the quote would end the string. Instead you write a backslash in front of it, which is an escape sequence:

```c
printf("Tab:\tBackslash:\\ Quote:\"\n");
```

`\t` is a tab, `\\` is a single backslash, and `\"` is a double quote. The output shows the tab as a gap, and the other two as the characters themselves. Escape sequences work in every string literal, including the format strings you pass to `printf`.

---

### Quiz

*These questions are written for this course.*

````quiz
What does strlen("Ada") return?
○ 4
→ Not quite. The zero byte isn't counted in the length.
◉ 3
→ Yes. The length counts the characters, not the zero byte at the end.
○ 0
→ Not quite. strlen counts the characters before the zero byte, which is 3 here.
````

````quiz
What is the position of the first character in a C string?
○ 1
→ Not quite. C starts counting positions at zero.
◉ 0
→ Yes. The first character is at position 0, and the second is at position 1.
○ -1
→ Not quite. Positions run from zero upwards.
````

````quiz
Which function adds text to the end of a string in C?
○ +=
→ Not quite. C doesn't allow += on strings. The operator is for numbers.
◉ strcat
→ Yes. strcat appends the second string to the end of the first.
○ append
→ Not quite. There's no standard append function in C.
````

---

### Try it in the runner

Change `name` to `"Grace Hopper"`, and predict the length and the bytes stored before you press **Run**. The length is 12 and the bytes stored are 13: `Grace Hopper` has 12 characters, the same as `Ada Lovelace`.

Then change the `greeting` line to use `"Hello"` and `"world"`, and predict the length. The text is `Hello, world!`, and its length is 13.

Finally, change `name[0]` to `name[40]`, and press **Run**. The program may print a strange character, print nothing useful, or crash. C doesn't check positions against the array's size, so this reads memory outside the array. That's a sign you've read outside the string. Change the position back to 0 before you go on.

---

Strings in C are arrays of characters with a zero at the end. Keeping track of the length and the size is the part that needs care, and the next step puts text from the user into an array.
