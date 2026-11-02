## Walkthrough: Vowel tests

`count_vowels` walks the word one character at a time, and asks whether each character is in the string "aeiou". `strchr` returns a pointer to the first match, or `NULL`. It also matches the terminating zero byte, which is why the loop checks `*p != '\0'` as well, so the end of the word never counts.

The empty word and the word with no vowels show the two ways to get zero: a loop that never runs, and a loop that runs but never matches. The word "education" has five vowels, one for each of a, u, a, i, and o, so it tests that the count doesn't stop at the first match.

For the uppercase extension, "HELLO" has no lowercase vowels, so the function as written returns 0. Whether that's right depends on the specification. The check should state the intended answer first, and the function should follow from it, not the other way round.
