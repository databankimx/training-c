## Homework: Bank account

Write an opaque type that represents a bank account, with a private balance and checked operations on it.

The module should:

* provide `bank_open`, which takes an opening balance and a pointer to an `int` status. It returns NULL and sets the status when the opening balance is negative, and it sets the status to `BANK_OK` otherwise
* provide `bank_deposit`, which returns `BANK_DEPOSIT_NOT_POSITIVE` when the amount is zero or less, and changes nothing
* provide `bank_withdraw`, which returns `BANK_INSUFFICIENT_FUNDS` when the amount is more than the balance, and changes nothing
* provide `bank_balance`, which takes a `const BankAccount *` and returns the balance
* keep the balance in `bank.c`, so `main.c` can't read or change it directly

In `main`, open an account with an opening balance of 0.0, then:

* deposit 100.0 and withdraw 30.0, then print `Balance: 70.00`
* try to withdraw 500.0, and print `Insufficient funds.` when the withdrawal is refused
* try to deposit -5.0, and print `Deposit must be positive.` when the deposit is refused
* print the balance again, with two decimal places

### What to check

The output should be:

```
Balance: 70.00
Insufficient funds.
Deposit must be positive.
Balance: 70.00
```

The last line should match the first. A refused withdrawal or deposit must leave the balance unchanged, and that's the most important rule in the exercise.

### Extensions

* Add a `bank_transfer` function that moves money from one account to another. Think about what should happen if the withdrawal succeeds and the deposit then fails, and how a return code can show it.
* Store a transaction count in the structure, and increase it on each successful deposit or withdrawal. Keep it in `bank.c`, and provide a getter.

---

*This exercise is not from the book. It practices the ideas in Chapter 11, with the return codes from Chapter 9.*
