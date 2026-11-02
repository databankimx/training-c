## Walkthrough: Weekday name

The names are stored in an array of seven `const char *` pointers, one per day. Each element points at the first character of a string literal, as the strings-and-pointers step showed. Because each name is its own string, the names can have different lengths, and nothing needs padding to the longest one.

The number from the user is one more than the index, because day 1 is at index 0. The program subtracts 1 when it builds `index`, so `days[index]` is the right name. `%s` prints the string that the chosen pointer refers to.

The range check comes first. The `if` tests `number < 1 || number > 7` before the array is read, so a value of 0 or 8 never produces an index at all, and `days[-1]` or `days[7]` is never reached. That order is the important part: the check protects the array, and reading the array comes only after it.

The extension about the array's size is the reason to keep the 7 in one place. With `sizeof days / sizeof days[0]`, the count is worked out from the declaration, since each element is one pointer. Adding an eighth name means changing the 7 in the declaration to 8, and the `sizeof` count then follows. A check that still uses a typed-in 7 would reject the new eighth day.

The wrap-around extension uses `%` on the day number after it's been adjusted: `(number % 7) + 1` gives the next day, with Sunday (7) wrapping to Monday (1).
