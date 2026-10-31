## Recursion

A function that calls itself is called recursive. It sounds like a trick, but many problems have this shape: a task that's made of smaller copies of the same task. Folders are a good example. A folder contains files and other folders, and each of those folders contains files and folders in turn. To list everything under a folder, you list its entries, and for each subfolder you do the same job again, on a smaller part of the tree.

Here's the program for this step, in `src/main.c`. The `sample` folder beside `src` holds a small tree, and the program lists it:

```c
void list_folder(const char *folder, int depth) {
    /* ... finds each entry in folder, prints its name indented by depth ... */
    if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        char child[1024];
        strcpy(child, folder);
        strcat(child, "\\");
        strcat(child, data.cFileName);
        list_folder(child, depth + 1);
    }
}
```

The full function is in `src/main.c`. It uses the Windows file functions from `<windows.h>`, because C's standard library has no way to list a folder. The runner is a Windows program, so the course can rely on those functions here. A `WIN32_FIND_DATAA` record describes each entry. `FindFirstFileA` starts the listing, `FindNextFileA` moves to the next entry, and `FindClose` ends it.

Press **Run**. The output lists every entry, with each level indented under its folder:

```
music
  song.txt
notes.txt
photos
  beach
    wave.txt
  holiday.txt
readme.txt
```

Windows returns entries in alphabetical order, so this listing comes out sorted by name at each level. Other file systems can return entries in a different order, and the contents stay the same, so the order is not something a program should depend on.

### What the recursion does

The function does one job: it lists the entries of one folder. For each entry, it prints the name. If the entry is a folder, the function calls itself on that folder, with `depth` one larger, to list what's inside. The call handles a smaller tree, and it finishes before the loop moves on to the next entry.

The recursion stops because the tree is finite. An ordinary file doesn't call the function, so it's the end of that branch. A folder with no subfolders gives a loop that calls nothing more. Every branch eventually reaches files, and the calls unwind back to the top.

Each call builds its own `child` path, and each call has its own `data` record and `find` handle, since those are local to the call. That's why a recursive call doesn't disturb the listing that called it.

The path is built in a buffer of 1024 bytes, and the program checks the length before copying anything into it. The check matters because the folder names come from the file system, and nothing limits how deep a tree can go. Copying without a check could write past the end of the buffer, which is the same overflow risk the strings chapter described.

### The depth parameter

The `depth` argument doesn't affect what gets listed. It only controls the indentation, so the output shows which folder each entry belongs to. Each call passes `depth + 1`, so entries inside a folder are indented one more step than the folder. The value is a counter that travels down the recursion, and it's the same idea as the parameters from earlier in the chapter.

The indentation comes from `printf("%*s%s\n", depth * 2, "", data.cFileName)`. The `*` in the format takes the width from an argument, so `depth * 2` spaces are printed before the name.

### Loops and recursion together

The loop handles the entries at one level, and the function call handles each level below. Recursion and loops often work together like this, and the loop is what visits each entry in turn.

### A warning about loops

A folder can contain a link that points back to an ancestor folder, and then the recursion never reaches a file or an empty folder. The program would keep going until something fails. Real tools track which folders they've visited, to avoid this. The sample tree has no such links, so this program is safe, but keep the risk in mind for any recursion over data you don't control.

---

### Quiz

*These questions are written for this course.*

````quiz
What stops the recursion in `list_folder`?
○ A counter that reaches a fixed limit.
→ Not quite. The depth grows as the tree goes deeper, but nothing stops at a fixed limit.
◉ The tree is finite, so every branch eventually reaches files, which don't call the function.
→ Yes. Each branch ends at a file or an empty folder.
○ The function returns a value to say it's finished.
→ Not quite. list_folder returns nothing, and it stops because the tree runs out.
````

````quiz
What does the `depth` parameter change in the output?
○ Which entries are listed.
→ Not quite. Every entry is listed whatever the depth.
◉ How far each entry is indented under its folder.
→ Yes. depth only controls the indentation.
○ The order in which the files appear.
→ Not quite. The file system decides the order, not depth.
````

---

### Try it in the runner

Rename `notes.txt` to `trip.txt` in the `sample` folder, and press **Run**. Predict where the new name appears in the listing before you press Run. Windows sorts the names, so `trip.txt` comes after `readme.txt` at the top level.

Then move `wave.txt` out of `beach` and into `music`, and predict where it appears. It goes under `music`, after `song.txt`, since the sort puts `wave.txt` after `song.txt`.

Then consider what would happen if `sample` contained a link back to `sample` itself. Describe what the recursion would do, and why the program would never finish. You don't need to build that case, since the lesson's warning explains it.

---

Recursion is a function that handles one level of a problem, and calls itself for the smaller problems inside it. The summary covers when recursion is the clearest choice, and when a loop is better.
