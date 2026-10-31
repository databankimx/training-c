## Walkthrough: Grade book

The highest and lowest are found in one loop. The first score sets both, which is why the test checks `i == 0`. Starting `highest` and `lowest` at zero would be wrong for a list of negative scores, and starting them at the first element is correct for any values.

The total is a plain `int`, which is safe here since the sum of four scores fits easily. The average divides the `double` form of the total by the `double` form of the count, so the fraction is kept. Dividing two `int` values would give 78, not 78.75.

Each `int_vector_at` call is checked by the loop bound, so the index never leaves the vector. The vector is freed once at the end, on the only exit path.
