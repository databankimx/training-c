## Walkthrough: Safe division

`safe_divide` starts with `found` false and a zero quotient, and only performs the division when the divisor isn't zero. So the division can't happen with a zero divisor, whichever function calls it. That's the point of putting the check inside the function that divides, rather than trusting each caller.

`print_division` reads `found` before it touches the quotient. The branch that prints "no answer" never reads the quotient at all, so the zero that sits in an empty result is never mistaken for a real answer.

For the extension with a fallback, printing -1 looks like a valid quotient to a reader, and a later calculation using that printed value would be wrong. The flag stays necessary, because the fallback is a choice made by the caller, and the flag is what lets the caller make it on purpose.
