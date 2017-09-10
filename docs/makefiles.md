Makefiles
================================================================================

Other Helpful Resources
--------------------------------------------------------------------------------
You can find online resources teaching practically every topic we cover in
our training sequence. These are much more thorough than anything we can
provide, though they're also a bit long-winded.

We've found a few that we like and provided links to them here:
* [Mr. Book (programmer blog)](http://mrbook.org/blog/tutorials/make/)
* [University of Maryland](https://www.cs.umd.edu/class/fall2002/cmsc214/Tutorial/makefile.html)


Compilation From the Command Line
--------------------------------------------------------------------------------
Introductory programming classes like ENGR101/151 have you learn C++ "from
scratch." They expect you to use basic text editors (like Sublime, Atom, or
even Gedit) to write your code, and they expect you to compile that code
into an executable by manually typing in `g++` commands into the terminal.

### Basic Compiler Syntax
Recall that the basic syntax for `g++` is as follows:

        g++ some_source_file.cpp -o some_source_file.exe
        ^(1)        ^(2)          ^(3)      ^(4)

1. `g++`
  * Calls the [gcc compiler](https://goo.gl/QKesGz), telling it that you
  want to compile a piece of code.
  * The `gcc` command is normally used to compile code written in C, though
  it [is actually possible](https://stackoverflow.com/questions/3178342/)
  to compile C++ code with it.
  * The command `g++` is basically the same as `gcc`, but you don't have to
  give it extra parameters telling it to enable C++-specific features.
2. `some_source_file.cpp`
  * The C++ file containing your code implementation.
3. `-o`
  * The thing you type after this is the location where `g++` will put your
    compiled executable.
4. `some_source_file.exe`
  * Write the binary to a file in the same directory named
    `some_source_file.exe`.

### Command-Line Arguments
Recall that you can add in additional **command-line arguments** when
calling `g++` to modify its behavior.

In ENGR101/151, the command line arguments that you typically use are:
* `-Wall`: Turns on almost all of g++'s compiler warnings. g++ will
  warn you about small style errors with your code that are a common
  source of bugs while also being easy to fix.
* `-Werror`: Causes g++ to treat compiler warnings as errors. If g++ throws
  any compiler warnings, your executable fails to compile. This forces you
  to fix all of your compiler warnings before being able to compile an
  executable.

### Potential Issues
In intro programming courses, every single time you want to compile your
code, you have to run a terminal command that looks something like:

        g++ some_source_file.cpp -o some_source_file.exe -Wall -Werror

The first time you type this command, you run the risk of making mistakes.
These could be typoes (like misspelling the name of
`some_source_file.cpp`), which would be briefly frustrating. Alternatively,
they could be disastrous mistakes such as typing...

        g++ some_source_file.cpp -o some_sourc

And then pressing `[TAB]` to autocomplete, producing...

        g++ some_source_file.cpp -o some_source_file.cpp -Wall -Werror
            ^ input file            ^ output file

Note that, when you run this command, you are telling g++ to 1) compile
your source file into an executable, and 2) **write that executable
directly on top of your original source file.**

If you don't have backups, **this would effectively delete all of your
existing code.**

Problems like these get worse as your projects grow larger.

### A Solution
Typing `g++` commands over and over is similar to duplicating code, which
we discussed in project0. Recall that the solution to this was to "factor
out" all of that duplicate code into a _function_ that you could call
whenever needed.

If that function contains a bug, all you have to do is fix that bug once in
that function's body. Once you do that, every part of your code that calls
that function will no longer be affected by that bug.

We can do something similar with compiler commands.

Makefiles
--------------------------------------------------------------------------------
A Makefile, as its name suggests, is a file providing instructions to a
built-in Linux utility called `make`. Makefiles contain **targets** that
you can `make` from a terminal with a command like `make {NAME_OF_TARGET}`.

Makefiles are easy to explain using examples, so we've included one below.

        # /home/your_username/maav/training/projectX/Makefile
        # ^(1)

        A_VARIABLE = g++
        A_DIFF_VAR = "-Wall -Werror "
        # ^(2)       ^(3)

        # (4)
        some_source_file : some_source_file.cpp
        # ^(5)              ^(6)
            $(A_VARIABLE) $^ -o $@ $(A_DIFF_VAR) # (7)

        # (4)
        another_source_file : another_source_file.cpp and_another.cpp
        # ^(5)              ^(6)
            $(A_VARIABLE) $^ -o $@ $(A_DIFF_VAR) # (7)

        # (4)
        yee :
        # ^(5)  ^(6)
            echo "yee" # (7)
            echo "NEEEEEEEEE" # (7)

1. Example filepath/filename
  * Unless you're [Doing Something
  Weird](https://www.gnu.org/software/make/manual/html_node/Makefile-Names.html),
  your Makefiles should always be named `Makefile`. Whenever you run
  `make`, `make` searches for a file called `Makefile` (or `makefile`, or
  `GNUmakefile`) in the Present Working Directory.
2. Variable Declaration
  * Sets a variable with the given name to the given value.
3. Variable Value
  * Everything to the right of the space character ("` `") after the
  equals-sign becomes the _literal_ value of the variable. This is
  explained in more detail further below.
4. Rules
  * Analogous to function definitions. Defines a particular "subunit" of the Makefile.
5. Targets
  * The "name" of a given rule. Analogous to a function's identifier (i.e.
    a function's name) in C++.
  * These must be flush with the left margin, i.e. **not indented.**
6. Prerequisites
  * The files monitored by the rule.
  * These must be indented with **tab characters.**
  * You **cannot indent with spaces when writing a Makefile.** (vim will use
    tab characters automatically, regardless of the settings in your
    `.vimrc`.)
7. Recipes
  * Analogous to function bodies. The commands that `make` runs in the
    terminal when you `make` that target.

Running the following in the terminal produces the following output. (These
commands are being executed in a single terminal session, one after the
other. Additional newlines are added for clarity.)

        your_username@ubuntu_thang:~/maav/training/projectX$ make yee
        echo "yee"
        yee
        echo "NEEEEEEEEE"
        NEEEEEEEEE

        your_username@ubuntu_thang:~/maav/training/projectX$ make some_source_file
        g++ some_source_file.cpp -o some_source_file "-Wall -Werror "

        your_username@ubuntu_thang:~/maav/training/projectX$ make another_source_file
        g++ another_source_file -o another_source_file.cpp and_another.cpp "-Wall -Werror "

        your_username@ubuntu_thang:~/maav/training/projectX$ make another_source_file
        make: 'another_source_file' is up to date.

        your_username@ubuntu_thang:~/maav/training/projectX$ vim and_another.cpp
        && echo "Edit and_another.cpp"
        Edit and_another.cpp

        your_username@ubuntu_thang:~/maav/training/projectX$ make another_source_file
        g++ another_source_file -o another_source_file.cpp and_another.cpp "-Wall -Werror "

        your_username@ubuntu_thang:~/maav/training/projectX$ rm another_source_file

        your_username@ubuntu_thang:~/maav/training/projectX$ make another_source_file
        g++ another_source_file -o another_source_file.cpp and_another.cpp "-Wall -Werror "

From this, you should note the following:
1. When `make`ing your project with a command in the terminal, the first
  argument after `make` is the **target (4)** that you want to `make`.
2. `make`ing a target means **running the commands written underneath the
   target in the terminal, line-by-line, in order.**
  * A given target can contain multiple commands.
  * Commands are Unix terminal commands that run in your active terminal
    window.
  * `make` will print the _exact command that it executes_ before actually
  executing it.
  * `make` will allow that command to _print output to the terminal_
    underneath that line.
3. You can only `make` a target if there have been **changes made to the
   prerequisites since the last time you `make`d that target**, or if **the
   target itself doesn't exist yet.** In other words, you can make a target
   if and only if:
  * You haven't yet compiled the executable produced by that target.
  * You've deleted the executable produced by that target.
  * You've edited the source files listed as prerequisites for that target.
4. You can avoid duplicating terminal commands by factoring out common
   functionality into **variables (2, 3)**.
  * This is particularly useful for compiler flags. Generally, if you want
    to change a compiler flag, you want to change them for every `make`
    target in the file. Storing the flags in a variable means that you only
    have to change them in one spot, rather than replacing them over and
    over all throughout the Makefile.
5. Makefiles have two useful **automatic variables** that you'll use
   frequently while writing your Makefiles: `$^` and `$@`.
  * `$^` means "the prerequisites for this target", i.e. **"everything to
  the right of the colon".**
  * `$@` means "the name of the target", i.e. **everything to the left of
  the colon.**
  * To better remember this, you can use your keyboard's number row. `@` is
  on the `2` key, which is **to the left** of the `7/^` key. Therefore,
  `2/@` represents the text on the **left-hand side** of the colon.
6. Variables store the literal text that follows the equals-sign.
  * You can **expand** a variable into its underlying value with the syntax
    `$({NAME_OF_VARIABLE})`.
  * Expansion converts the variable into the _exact_ string of text that
    followed the equals-sign when the variable's value was first assigned.
    You can see this from the output of `make some_source_file`. The
    double-quotes around `-Wall -Werror ` were included in the final
    terminal command.
