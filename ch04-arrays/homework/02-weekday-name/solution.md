## Walkthrough: Weekday name

The names are stored in a two-dimensional `char` array, `days[7][10]`. Each row holds one name, and the second number is the row width: ten characters, enough for `Wednesday` (nine letters) and its zero byte. Each string literal in the braces fills one row. A row can be printed with `%s`, since it's a string inside the array.

The number from the user is one more than the index, because day 1 is at index 0. The program subtracts 1 when it builds `index`, so `days[index]` is the right row.

The range check comes first. The `if` tests `number < 1 || number > 7` before the array is read, so a value of 0 or 8 never produces an index at all, and `days[-1]` or `days[7]` is never reached. That order is the important part: the check protects the array, and reading the array comes only after it.

The extension about the array's size is the reason to keep the 7 in one place. With `sizeof days / sizeof days[0]`, the count is worked out from the declaration. Adding an eighth name means changing the 7 in the declaration to 8, and the `sizeof` count then follows. A check that still uses a typed-in 7 would reject the new eighth day.

The wrap-around extension uses `%` on the day number after it's been adjusted: `(number % 7) + 1` gives the next day, with Sunday (7) wrapping to Monday (1).
