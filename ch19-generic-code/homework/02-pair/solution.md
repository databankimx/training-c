## Walkthrough: Pair

Each structure is written out for its two types, and each function is written for its structure. The compiler checks every use, because the types are in the declarations. A mismatch, such as passing the string pair to the int-string print function, is an error at compile time.

The cost is visible in the file. Each new combination of types needs another structure and two functions, and the code repeats the same shape each time. A C++ class template writes that shape once, and the compiler generates each version. The C version trades that convenience for explicit code, which is easier to read but longer to maintain.

For the extension about `swapped`, the result of swapping an `int` and a string is a string and an `int`, which is a fourth combination. A program with four pair types needs four structures in C, while the C++ template needs one definition.

A single `void *` pair would hold both values without their types. A print function would then have to know both types, and the compiler couldn't check that the function and the pair agree. The explicit structures avoid that risk, at the price of the repetition.
