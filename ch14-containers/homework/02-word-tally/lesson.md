## Homework: Word tally

Write a program that counts how often each word appears in a list, and reports the most common word.

The program should:

* create a `HashTable` to hold the counts
* count these words, in this order: `red`, `blue`, `red`, `green`, `blue`, `red`
* print each distinct word and its count, in sorted order, as `blue: 2`
* find the word with the highest count, and print `Most common: red`

Store the words in a `const char *` array, and use an index loop to count them. Because a hash table has no order, keep a separate array of the distinct words as you count, and sort that array before printing. To find the most common word, keep the best word and best count found so far, and update them in the printing loop.

### What to check

The output should be:

```
blue: 2
green: 1
red: 3
Most common: red
```

The words print in sorted order, so `blue` comes first. The most common word is found by comparing counts, not by position.

### Extensions

* Ignore case, so `Red` and `red` count as the same word. Decide where the conversion belongs, and say why.
* Print every word that ties for the highest count. Think about whether you need one pass or two.

---

*This exercise is not from the book. It practices the ideas in Chapter 14.*
