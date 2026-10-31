## Greeting card

The example reads the name the same way the user-input step did: `fgets` reads the whole line, and `strcspn` removes the newline. The flush before the question makes it appear before the program waits for the input box.

`strlen` then counts the characters in the cleaned name. Because the newline was removed first, the count is the name's length alone. If the newline had stayed, the count would be one too high, and the card would say "6 letters" for `Grace`.

The extension asks for the letters only. `strlen` counts spaces as characters, so `Ada Lovelace` gives 12. Counting the letters means looping over the characters and counting those for which `isalpha` is true, which comes from `<ctype.h>`. The loop is a topic for the loops chapter.
