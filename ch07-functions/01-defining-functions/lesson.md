## Defining functions

So far, each program has been one long `main`. That works while the program is short, but a larger program repeats the same steps in several places, and the same code in several places is hard to change. A function gives a block of code a name, so you write it once and call it wherever you need it.

Here's the program for this step, in `src/main.c`:

```c
void greet(void) {
    printf("I just got executed!\n");
}
```

The definition has four parts. `void` is the return type, which says the function gives back nothing. `greet` is the name, followed by parentheses. The braces hold the body, which is the code that runs when the function is called.

The parentheses hold `void` here, and that matters. In C, `greet()` with nothing inside means the parameters are not specified, which is an older rule. Writing `(void)` says plainly that the function takes no parameters. Use `(void)` for every function with no parameters, as this course does.

Calling the function is one line, the function's name followed by parentheses:

```c
printf("Before the calls\n");
greet();
greet();
printf("After the calls\n");
```

Press **Run**. The output is:

```
Before the calls
I just got executed!
I just got executed!
After the calls
```

The function runs twice, because it's called twice. Each call jumps to the body, runs it, and comes back to the line after the call.

### Declaring before use

The compiler reads a file from top to bottom. When it sees `greet();` in `main`, it needs to know that `greet` exists, and what kind of function it is. The program handles this with a declaration near the top:

```c
void greet(void);
```

A declaration gives the function's name, return type, and parameters, and ends with a semicolon. It doesn't contain a body. In C this declaration is called a prototype. The definition can then appear anywhere in the file, after `main` if you prefer. Without the declaration, the call in `main` comes before the compiler has seen the function. Recent versions of gcc refuse to build the program and report the function as not declared.

Many programmers put `main` at the top and the functions after it, using declarations to make that work. Others define each function before it's used. Either is fine, as long as every name is declared before the code that calls it.

---

### Quiz

*These questions are written for this course.*

````quiz
What does the `void` before a function's name mean?
○ The function takes no parameters.
→ Not quite. The `(void)` in the parentheses says that.
◉ The function returns no value.
→ Yes. void means there's no return value.
○ The function does nothing when called.
→ Not quite. A void function can do a great deal. It just doesn't return a value.
````

````quiz
Why does `greet();` need a declaration when it's called before its definition?
○ So the function can run faster.
→ Not quite. A declaration has nothing to do with speed.
◉ So the compiler knows the function exists when it reaches the call.
→ Yes. The compiler reads top to bottom, so the name must be known by the time the call appears.
○ So the function can access main's variables.
→ Not quite. Functions don't share variables with main unless you pass them in.
````

---

### Try it in the runner

Move the definition of `greet` above `main`, and delete the declaration. Press **Run**. The program still builds, because the definition comes before the call.

Then put the definition back below `main`, and delete the declaration. Press **Run** again. This time the build fails, because the call in `main` comes before the compiler has seen `greet`. Put the declaration back before you continue.

---

A function is a named block of code, and a declaration is how the compiler learns that the name exists. The next step gives functions inputs, so the same function can do different work each time it's called.
