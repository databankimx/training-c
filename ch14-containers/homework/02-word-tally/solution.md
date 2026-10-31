## Walkthrough: Word tally

The loop does two jobs at once. Before each word is counted, the program asks the table whether the word has been seen. A word that's missing is added to `distinct`, so the array ends up holding each distinct word exactly once, in first-seen order. Then the word is counted.

The distinct words are sorted with `qsort`, because the hash table itself has no order. The printing loop reads each count back with `hash_table_get`, so the table is the single source of the numbers.

The most common word is found in the same loop that prints. `best_count` starts at zero, so the first word with a positive count becomes the best, and a tie keeps the word that was printed first. The extension about ties needs a second pass once the highest count is known, or a list that collects every word equal to it.

The table is freed once, after the last use. The distinct array holds pointers into the words array, not copies, so nothing needs freeing for it.
