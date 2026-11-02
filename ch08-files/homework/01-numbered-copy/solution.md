## Walkthrough: Numbered copy

The program opens both files, and checks each one before it uses it. If the output file fails to open, the input file is closed before the program returns, so no file is left open by mistake.

The loop reads with `fgets`, and it removes the newline before writing. Each line is written with `fprintf` in the form `number. text`, and the newline is added back by the format, which keeps the output lines separate.

The counter increases once per line, before the line is written, so the first line is numbered 1. The final message uses the same counter, so it reports the number of lines actually written.

For the extension about empty lines, the check that skips a line goes before `count++`. A line that's skipped is never numbered, and the counter only moves for lines that are written.
