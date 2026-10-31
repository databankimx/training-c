## Walkthrough: Address book

The contacts are stored in an array of `Contact` structures, initialized in braces, one inner pair of braces per contact. The count comes from `sizeof contacts / sizeof contacts[0]`, so the loop's bound is worked out from the declaration rather than typed in twice. The extension's question about repeated sizes is answered by that line: adding a contact changes the array, and the loop follows.

The name is read as a line and its newline removed, so the comparison is between the typed name and the stored one, with nothing extra on the end.

`_stricmp` compares two strings without regard to letter case. It's a Windows function, in the same family as the file functions used in the file chapter. It returns 0 when the strings match, so `== 0` is the test. That's why `alan` finds `Alan`, and the output shows the stored spelling.

The `break` sits right after the match is printed. The loop stops at the first contact with that name, and `found` records whether anything matched, so the `if` after the loop prints the not-found message only when the search failed.
