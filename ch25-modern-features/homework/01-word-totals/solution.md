## Walkthrough: Word totals

The array holds each word next to its count, so one structure is one row of the list. The first loop uses a pointer to each row, and reads the named members, which is the C form of unpacking a binding. The second loop reads the counts directly and adds them.

The order of the output is the order of the array. The C++ map sorted its keys, so "pear" would come last whatever the insertion order. Here the order is the one written in the initializer, and the program does not sort it. Writing the entries alphabetically gives the same output, and any other order gives a different one, which is why the lesson calls the order the programmer's job.

For the extension that returns -1 for a missing word, the caller must remember to check for -1, and no type says so. A caller that adds -1 to a total would be wrong without any warning. The optional structure from the chapter puts the missing case in a flag the caller must read, which is the safer design.
