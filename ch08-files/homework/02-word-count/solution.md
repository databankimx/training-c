## Walkthrough: Word count

The file is opened twice, once for each count. The first pass reads whole lines with `fgets`, and the count goes up once per line that was read. The second pass reads words with `fscanf`, where `%255s` skips the spaces and newlines between words and stops at the next one. The word is stored in `word`, and the count goes up while `fscanf` returns 1.

Each pass ends with `fclose`, and the second `fopen` starts reading from the beginning of the file again. That's why the file is reopened rather than rewound.

The line count depends on the file ending with a newline after the last line. `fgets` returns the final line either way, so the count is 3 whether or not there's a newline at the very end.

The word count treats punctuation as part of a word. `dog.` is one word, as the exercise says. Counting words that way is a simple rule, and it matches what a reader sees on the page.
