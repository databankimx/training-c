## Walkthrough: Leap-year tests

The function checks the rules in the order that matters. A year divisible by 400 is a leap year whatever else is true, so that test comes first. A year divisible by 100 but not 400 is not a leap year, and that test comes second, so it isn't overridden by the divisible-by-4 rule. Any other year is a leap year exactly when it's divisible by 4.

The four checks cover the rule's cases. 2024 is divisible by 4 and not by 100. 2023 is not divisible by 4. 1900 is divisible by 100 but not 400, which is the case most often gotten wrong. 2000 is divisible by 400, the other exception.

The extension cases fill in the rest. 1600 is divisible by 400, and 2028 is divisible by 4 and not 100. Changing the function to get 1900 wrong, by removing the century test, makes the 1900 check fail, which shows that the edge cases are what catch the mistake.
