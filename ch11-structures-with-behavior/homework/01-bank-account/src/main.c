#include <stdio.h>

#include "bank.h"

int main(void) {
    int status;
    BankAccount *account = bank_open(0.0, &status);
    if (account == NULL) {
        printf("opening balance cannot be negative\n");
        return 1;
    }

    bank_deposit(account, 100.0);
    bank_withdraw(account, 30.0);
    printf("Balance: %.2f\n", bank_balance(account));

    if (bank_withdraw(account, 500.0) == BANK_INSUFFICIENT_FUNDS) {
        printf("Insufficient funds.\n");
    }
    if (bank_deposit(account, -5.0) == BANK_DEPOSIT_NOT_POSITIVE) {
        printf("Deposit must be positive.\n");
    }
    printf("Balance: %.2f\n", bank_balance(account));

    bank_close(account);
    return 0;
}
