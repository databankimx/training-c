## Walkthrough: Employee pay

The `Manager` structure begins with an `Employee`, so `&boss.base` is an `Employee *` that points at the start of the manager. `print_pay` calls `employee->pay(employee)`, which runs whichever pay function the object holds. The manager's object holds `manager_pay`, so the manager's version runs, and `print_pay` never needs to know that the object is a manager.

`manager_pay` converts the `Employee` pointer back to a `Manager *` to reach the bonus. That's valid because the employee is the first member of the manager, so the two addresses are the same. The same rule covered the shapes exercise.

C has no `protected` level, and the bonus is a plain member of `Manager`. Anyone who can see the structure can read it, so the exercise's requirement that the bonus be private can only be met with an opaque type, defined in a single source file, as the encapsulation step of the structures chapter showed. The exercise's extension about making the bonus protected rests on the same limit.

The extension about passing the employee by value shows slicing in C terms. A copy of the employee is copied as an `Employee`, and any manager fields that came after it are not copied. Passing a pointer keeps the whole object, so the manager's pay function still runs.
