#include "bank.h"

#include <stdlib.h>

struct BankAccount {
    double balance;
};

/* Returns NULL and sets *status when the opening balance is negative. */
BankAccount *bank_open(double opening_balance, int *status) {
    if (opening_balance < 0) {
        *status = BANK_NEGATIVE_OPENING;
        return NULL;
    }
    BankAccount *account = malloc(sizeof *account);
    if (account == NULL) {
        *status = BANK_NEGATIVE_OPENING;
        return NULL;
    }
    account->balance = opening_balance;
    *status = BANK_OK;
    return account;
}

void bank_close(BankAccount *account) {
    free(account);
}

/* The balance changes only when the amount is valid, so a refused deposit leaves it as it was. */
int bank_deposit(BankAccount *account, double amount) {
    if (amount <= 0) {
        return BANK_DEPOSIT_NOT_POSITIVE;
    }
    account->balance += amount;
    return BANK_OK;
}

int bank_withdraw(BankAccount *account, double amount) {
    if (amount > account->balance) {
        return BANK_INSUFFICIENT_FUNDS;
    }
    account->balance -= amount;
    return BANK_OK;
}

double bank_balance(const BankAccount *account) {
    return account->balance;
}
