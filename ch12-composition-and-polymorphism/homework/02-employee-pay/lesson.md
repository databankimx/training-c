## Homework: Employee pay

Write an `Employee` structure and a `Manager` structure built on it, so that each kind of employee computes its own pay, and a single function prints any employee's pay.

The program should:

* define `Employee`, with a `monthly_salary` member of type `int` and a function pointer member, `pay`, that takes a `const Employee *` and returns the monthly pay
* give `Employee` a pay function that returns `monthly_salary`
* define `Manager` with an `Employee` as its first member, and an `int` member `bonus`
* give `Manager` a pay function that returns the salary plus the bonus, and set its pointer when the manager is created
* write `make_employee` and `make_manager` functions, each of which sets the members and the pay pointer
* define `print_pay`, which takes a `const Employee *` and prints `Monthly pay: ` followed by the value of its pay function
* in `main`, create an `Employee` with a salary of 3000, a `Manager` with a salary of 4500 and a bonus of 800, and print the pay for each with `print_pay`

### What to check

The output should be:

```
Monthly pay: 3000
Monthly pay: 5300
```

The second line uses the manager's pay function, even though `print_pay` only knows about `Employee`. If it prints 4500, the manager's pointer was set to the employee's function.

### Extensions

* Add a `Director` that is built on `Manager` with an extra amount, and give it a pay function. Think about which pay function a director's pointer should hold, and how the director's function reaches the bonus.
* Change `print_pay` so it takes the `Employee` by value, and check the output. Explain what the copy loses, using the word slicing from the polymorphism step.

---

*This exercise is not from the book. It practices the ideas in Chapter 12.*
