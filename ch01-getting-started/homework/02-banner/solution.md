## Banner

The example prints the three lines one at a time, so each line can be checked against the banner on its own.

The box is twelve characters wide. The text `C is fun` is eight characters long. Add two spaces, one on each side, and you have ten characters inside the asterisks. Each side adds one asterisk and one space, so the middle line is twelve characters long too. The top and bottom lines are twelve asterisks.

The extension asks for the width of a longer phrase. Count the characters in the text, add four (two spaces and two asterisks), and that's the number of asterisks for the top and bottom lines. For `Learning C is great`, that's 19 characters plus 4, so 23 asterisks.

The `%s` in the second extension is a placeholder for a string. `printf` replaces it with the text you pass after the format, which is the idea behind printing the banner for any phrase.
