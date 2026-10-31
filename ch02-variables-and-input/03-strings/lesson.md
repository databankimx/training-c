## Strings

C has no string type. A string is an array of `char` values, and it ends with a zero byte, written `'\0'`, which marks where the text stops. The program in `src/main.c` declares one:

```c
char name[] = "Ada Lovelace";
```

Press **Run**. The output is:

```
Name: Ada Lovelace
Length: 12
Bytes stored: 13
First letter: A
Same as "Ada"? no
```

### Format specifiers

The program uses `printf` with several placeholders. Each one starts with `%` and says what kind of value goes in that spot:

| Specifier | Type it's for | Used in this program | Example output |
|---|---|---|---|
| `%s` | A string, which is a char array ending in a zero byte | `Name: %s` | `Name: Ada Lovelace` |
| `%zu` | A `size_t`, the type `strlen` and `sizeof` return | `Length: %zu` | `Length: 12` |
| `%c` | A single `char` | `First letter: %c` | `First letter: A` |

The specifier must match the type of the value. `%s` given a `char` instead of a string prints garbage, and `%d` given a string prints a meaningless number. A value of the wrong type can crash the program, so match them carefully.

Two more are worth knowing. `%%` prints a single percent sign. `%.2f` prints a `double` with two digits after the point, as the arithmetic lesson used.

### Length and size are different

`strlen` counts the characters before the zero byte, so `Ada Lovelace` has a length of 12. `sizeof name` is the size of the whole array, which is 13, because the zero byte takes a place too. Confusing the two is one of the most common sources of bugs in C text code: an array sized from the length, with no room for the zero, can't hold the string it was meant to.

### Strings are arrays

`name[0]` is the first character, `A`, and `name[11]` is the last, `e`. Indexing starts at 0, as it did for arrays in the arrays chapter. A string literal, such as `"Ada"`, is also an array of characters, and it has its own zero byte at the end.

### Comparing strings

`==` compares the addresses of two arrays, not their text, so `name == "Ada"` is not the test you want. `strcmp` compares the text. It returns 0 when the two strings are equal, which is why the program writes `strcmp(name, "Ada") == 0`.

### Copying and the length trap

`strcpy` copies text into an array, but it doesn't check that the array is big enough. If the text is longer, it writes past the end of the array, which is a buffer overflow, a common cause of security problems. Use `strncpy` or `snprintf`, which take the array's size and stop before it overflows, and always check that the destination is large enough for the text.

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

---

### Try it in the runner

Change `name` to `"Grace Hopper"`, and predict the length and the bytes stored before you press **Run**. The length is 12 and the bytes stored are 13: `Grace Hopper` has 12 characters, the same as `Ada Lovelace`.

---

Strings in C are arrays of characters with a zero at the end. Keeping track of the length and the size is the part that needs care, and the next step puts text from the user into an array.
