## Homework: Address book

Write a program that keeps a small list of contacts, and looks up a phone number by name.

The program should:

* define a structure called `Contact`, with a `char` array member `name` and a `char` array member `phone`
* create an array of three contacts, initialized with brace initialization, with these entries: `Ada` with `555-0101`, `Grace` with `555-0102`, and `Alan` with `555-0103`
* ask for a name, with the prompt `Enter a name: `, and read it as a whole line with `fgets`, removing the newline
* use a `for` loop to find the contact with that name, and print `Ada: 555-0101` for a match
* print `No contact named <name>.` when no contact matches

Flush the output after the prompt, with `fflush(stdout)`. The loop should stop at the first match, so think about where a `break` belongs.

### What to check

Try these names:

* `Grace` should print `Grace: 555-0102`
* `alan` should print `Alan: 555-0103`, since the comparison ignores letter case
* `GRACE` should print `Grace: 555-0102`
* `Bob` should print `No contact named Bob.`

The output shows the name as it's stored in the array, not as it was typed. Think about why an address book should match regardless of case, and what a case-sensitive search would make a user do.

### Extensions

* Add a fourth contact by changing the array, and check that the search finds it. Think about how many places the array size appears in the program, and whether you can avoid repeating it.
* Print every contact when the name is `all`, using a second loop.

---

*This exercise is not from the book. It practices the ideas in Chapter 10, with the loops from Chapter 6.*
