#ifndef BANK_H
#define BANK_H

#define BANK_OK 0
#define BANK_NEGATIVE_OPENING -1
#define BANK_DEPOSIT_NOT_POSITIVE -2
#define BANK_INSUFFICIENT_FUNDS -3

typedef struct BankAccount BankAccount;

BankAccount *bank_open(double opening_balance, int *status);
void bank_close(BankAccount *account);

int bank_deposit(BankAccount *account, double amount);
int bank_withdraw(BankAccount *account, double amount);
double bank_balance(const BankAccount *account);

#endif /* BANK_H */
