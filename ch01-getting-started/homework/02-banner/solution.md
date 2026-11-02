## Banner

The example prints the three lines one at a time, so each line can be checked against the box on its own.

The greeting, `Hello!`, is six characters long. The middle line adds a space on each side and an asterisk at each end, which makes it ten characters: `* Hello! *`. The top and bottom lines are ten asterisks, so all three lines match.

The extension asks for a count of the stars rather than typed-out stars. To print a line of asterisks for any width, you'd repeat a `printf` for each one, and the loops chapter shows how to do that in one statement.

The second extension, flushing after each line, leaves the box exactly as it was. Flushing only changes when the text is sent to the screen, not what it says.
