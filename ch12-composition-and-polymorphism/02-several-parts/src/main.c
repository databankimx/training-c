#include <stdio.h>
#include <string.h>

typedef struct {
    int salary;
} Employee;

typedef struct {
    Employee base;
    int bonus;
} Programmer;

typedef struct {
    char code[8];
} Badge;

typedef struct {
    Programmer programmer;
    Badge badge;
} Engineer;

void programmer_set_salary(Programmer *p, int salary) {
    p->base.salary = salary;
}

int programmer_get_salary(const Programmer *p) {
    return p->base.salary;
}

int main(void) {
    Engineer e;
    programmer_set_salary(&e.programmer, 50000);
    e.programmer.bonus = 15000;
    strcpy(e.badge.code, "B-42");

    printf("Salary: %d\n", programmer_get_salary(&e.programmer));
    printf("Bonus: %d\n", e.programmer.bonus);
    printf("Badge: %s\n", e.badge.code);

    // Try: add e.programmer.base.salary = 60000; to main, and predict whether it compiles before you press Run.
    return 0;
}
