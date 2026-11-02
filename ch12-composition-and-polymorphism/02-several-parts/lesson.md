## Several parts and protection

Inheritance in C++ has three access levels for members. `public` members are visible to everyone, `private` members only inside their own class, and `protected` members inside the class and in classes derived from it. C has none of these. A structure's members are all visible to any code that can see the structure's declaration, and nothing in the language separates a family of types from outsiders. This step shows what C offers in place of protection, and how a structure can be built from several parts.

Here's the program for this step, in `src/main.c`. The base structure holds a salary, and a programmer structure contains it:

```c
typedef struct {
    int salary;
} Employee;

typedef struct {
    Employee base;
    int bonus;
} Programmer;
```

The functions for the programmer work through the embedded base, as the previous step did. Access to the salary goes through two small functions:

```c
void programmer_set_salary(Programmer *p, int salary) {
    p->base.salary = salary;
}

int programmer_get_salary(const Programmer *p) {
    return p->base.salary;
}
```

Press **Run**. The output is:

```
Salary: 50000
Bonus: 15000
Badge: B-42
```

### Several parts

C++ lets a class inherit from more than one base. In C, a structure contains several parts, each as its own member. Here an engineer contains a programmer and a badge:

```c
typedef struct {
    Programmer programmer;
    Badge badge;
} Engineer;
```

Each part keeps its own members. `e.programmer.bonus` and `e.badge.code` are reached through the member names, so there's no question about which part is meant. C++ needs extra rules when two bases have members with the same name. C needs none, because every member is always named through its part.

### Protection is a convention in C

Because C has no protected level, a rule such as "only the programmer's functions may change the salary" is a convention. The program follows it by writing `programmer_set_salary` and not writing to `p->base.salary` from `main`. Nothing in the language enforces the rule, and the next line in `main` could break it. The Try section shows this.

C does have a way to make the rule enforced: an opaque type, as the encapsulation step of the last chapter showed. If the structure is defined only in a source file, code outside that file can't reach the salary at all. That's the nearest C has to `private`, and it can be applied to a family of structures by defining them in one file.

### Choosing what to expose

The rule the C++ lesson gives still applies. Keep a member hidden if only its own functions need it. Expose it through a function if other code needs to use it. Only put it in a header, where everything can see it, when the rest of the program really needs direct access. Each step outward gives more code the power to change the member, so the smallest exposure that works is the safest.

---

### Quiz

*These questions are written for this course.*

````quiz
Which C mechanism is the nearest equivalent of a `private` member?
○ A member declared with the const keyword.
→ Not quite. const stops writes through a pointer, but it doesn't hide the member from code that can see the structure.
◉ An opaque type, with the structure defined only in one source file.
→ Yes. Code outside that file can't reach the members at all.
○ A member whose name starts with an underscore.
→ Not quite. A naming convention doesn't stop the compiler from accepting the access.
````

````quiz
How does a C structure with several parts refer to each part's member?
○ By name alone, such as bonus, and the compiler picks the right part.
→ Not quite. C requires the path through the parts, so each member is named through its part.
◉ Through the part's name, such as e.programmer.bonus.
→ Yes. Each part keeps its own members, and the path says which one is meant.
○ Through a method call on the structure.
→ Not quite. C has no methods, so members are reached by name.
````

---

### Try it in the runner

Add `e.programmer.base.salary = 60000;` to `main`, and predict whether it compiles before you press **Run**. It compiles and runs, because the structure is visible to `main`, and C has no level that stops it. The salary changes, and the convention that `programmer_set_salary` is the only way in has been broken. Remove the line before you continue.

Then move the definition of `Employee` into a separate file, leaving `main.c` with only a declaration, as the encapsulation step did. The program stops building, and it's not only the salary line that fails. `Programmer` holds an `Employee` by value, so the compiler needs the whole definition of `Employee` to build it. An opaque type avoids this by keeping the member behind a pointer, which is why the encapsulation step used one. Restore the definition before you continue.

---

A C structure gets several parts by containing them, and its members are always named through their part. C has no protected level, so a rule about who may change a member is enforced only by a convention, or by hiding the structure in one source file. The next step covers polymorphism, which C builds from a table of function pointers.
