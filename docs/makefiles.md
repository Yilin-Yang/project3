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

Recall that you can add in additional **command-line arguments** when
calling `g++` to modify its behavior.
