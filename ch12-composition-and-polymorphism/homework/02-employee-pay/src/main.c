#include <stdio.h>

typedef struct Employee Employee;

struct Employee {
    int monthly_salary;
    int (*pay)(const Employee *self);
};

typedef struct {
    Employee base;
    int bonus;
} Manager;

int employee_pay(const Employee *self) {
    return self->monthly_salary;
}

int manager_pay(const Employee *self) {
    const Manager *manager = (const Manager *)self;
    return self->monthly_salary + manager->bonus;
}

Employee make_employee(int salary) {
    Employee e = {salary, employee_pay};
    return e;
}

Manager make_manager(int salary, int bonus) {
    Manager m = {{salary, manager_pay}, bonus};
    return m;
}

void print_pay(const Employee *employee) {
    printf("Monthly pay: %d\n", employee->pay(employee));
}

int main(void) {
    Employee staff = make_employee(3000);
    print_pay(&staff);

    Manager boss = make_manager(4500, 800);
    print_pay(&boss.base);

    return 0;
}
