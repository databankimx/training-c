## Walkthrough: Leap year

The example reads the year as text and converts it with `strtol`, then stores the whole rule in one `bool`. Read the condition as two cases. A year that's divisible by 4 but not by 100 is a leap year, and so is any year divisible by 400. Every other year is not.

The `&&` binds more tightly than `||`, so the parentheses don't change the result: the condition would mean the same without them. They're there so the two cases are visible, which matters to the next reader.

The check for 1900 is the important one. It's divisible by 4, so a program that only tested divisibility by 4 would call it a leap year. The `% 100 != 0` part of the first case catches it, and the year fails both cases. The check for 2000 works the other way: it's divisible by 100, so the first case fails, but it's divisible by 400, so the second case passes.

The output uses an `if` with two `printf` calls, one for each answer, so the words in the sentence follow the result. The extension asks you to write the same rule without an `if`, which is the `bool` alone, printed as a number.
