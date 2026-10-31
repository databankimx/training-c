## Return codes

A program often reaches a point where it can't carry on normally. A value is missing, a number is out of range, or a file won't open. C has no exceptions, so a function that can fail reports it through its return value. The caller checks that value, and decides what to do.

Here's the program for this step, in `src/main.c`. The function refuses an age below 18 by returning a code:

```c
#define ACCESS_OK 0
#define ACCESS_TOO_YOUNG 1

int check_access(int age) {
    if (age < 18) {
        return ACCESS_TOO_YOUNG;
    }
    printf("Access granted - you are old enough.\n");
    return ACCESS_OK;
}
```

The function returns one of two named codes. `ACCESS_OK` is 0, and `ACCESS_TOO_YOUNG` is 1. The names say what each code means, so the caller doesn't need to remember which number is which.

The code that calls the function stores the result and tests it:

```c
int age = 15;
int status = check_access(age);
if (status == ACCESS_TOO_YOUNG) {
    printf("Access denied - you must be at least 18 years old.\n");
    printf("Age is: %d\n", age);
}
```

Press **Run**. The output is:

```
Access granted - you are old enough.
Access denied - you must be at least 18 years old.
Age is: 15
```

The first call passes, and prints its message. The second call returns `ACCESS_TOO_YOUNG`, and the `if` in `main` runs the denial branch. Nothing in the function stops the program. The caller decides what the failure means.

### Every call has to be checked

A return code works only when the caller checks it. Look at the first call in the program:

```c
int status = check_access(25);
if (status != ACCESS_OK) {
    printf("Unexpected failure.\n");
}
```

The check is there, and the message is printed if the call fails. Leave the check out, and nothing happens. The program carries on with the code ignored, and the compiler doesn't complain, because a return value can be ignored in C without any warning. That's the main weakness of return codes, and it's why many C programs test their return values carefully. A code that can fail must be checked at each point where it's called, and a function that calls a failing function has to pass the failure on, or deal with it.

Exceptions in C++ avoid part of this, because a thrown error can't be ignored in the same way, and it crosses several functions without each one passing it along. C doesn't have that. The price of the simpler language is discipline at every call.

### Choosing a code

Return codes can be numbers, as this step's are, or values of an `enum`, which give each code a name in one place:

```c
enum access_result { ACCESS_OK, ACCESS_TOO_YOUNG };
```

An `enum` groups related names, and the compiler checks that the function returns one of them. The step uses `#define` names, which work the same way here. Either form is common in C code.

A function can also return a value that's not a code at all, such as a pointer that's `NULL` on failure, as `fopen` does. The next step covers how to find out why a library call failed.

---

### Quiz

*These questions are written for this course.*

````quiz
What happens when a caller ignores the return code of a failing function?
○ The program stops with an error message.
→ Not quite. That's what an uncaught exception does in C++, and C has no equivalent.
◉ The program carries on, and nothing reports the failure.
→ Yes. Return codes only report failure to a caller who checks them.
○ The compiler refuses to build the program.
→ Not quite. C lets a return value be ignored without a warning.
````

````quiz
Why are the codes written as `ACCESS_OK` and `ACCESS_TOO_YOUNG` rather than 0 and 1?
○ Because the compiler requires named constants.
→ Not quite. The compiler accepts plain numbers.
◉ Because the names say what each code means, so the caller doesn't have to remember the numbers.
→ Yes. Named codes make the test in the caller readable.
○ Because 0 and 1 are not allowed as return values.
→ Not quite. Any int can be returned.
````

---

### Try it in the runner

Delete the `if` around the second `check_access` call, so the program looks like this:

```c
int status = check_access(age);
printf("Access denied - you must be at least 18 years old.\n");
printf("Age is: %d\n", age);
```

Predict the output before you press **Run**. The denial message prints whether or not the check failed, because nothing tests the status. Then change `age` to 25, and press **Run** again. The denial message still prints, even though the age passes the check. Restore the `if` before you continue.

---

A return code reports failure to whoever calls the function, and that caller decides what to do. The next step shows how the standard library tells you why a call failed.
