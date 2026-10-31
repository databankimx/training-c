## Walkthrough: Bank account

The balance is a field of `struct BankAccount`, defined only in `bank.c`. `main.c` holds a pointer and calls functions, so the only way to change the balance is through a function that checks the change first.

Each operation checks its amount before touching the balance. `bank_deposit` refuses a zero or negative amount, and `bank_withdraw` refuses an amount above the balance. Both return before any assignment, so a refused operation can't leave the balance half-changed. That's the rule the exercise's final line tests.

`bank_open` returns NULL when the opening balance is negative, and it reports the reason through `status`. The status is the way to tell `main` which check failed, since C has no exception to carry the reason.

The extension about transfers shows why return codes need care. If the withdrawal succeeds and the deposit then fails, the money has left one account without arriving in the other. A transfer function must check both steps before it changes either balance, or undo the withdrawal if the deposit is refused.
