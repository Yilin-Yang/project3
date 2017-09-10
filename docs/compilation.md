The Compilation Process
================================================================================
Compilation (also called **building**) is the multi-step process that
converts a source file or a set of source files (a **codebase**) into an
**executable** that you "run" on your computer. C++, the programming
language used by MAAV, must be compiled into an executable before it can be
used.

You don't need to know all of the details of how this works, but there are
a few steps of the process that are important for the work you'll do for
MAAV and the work you'll do in your first- and second-year EECS courses.
We'll cover those here!

Kinds of Programming Language
--------------------------------------------------------------------------------
Programming languages typically fall into two main categories: interpreted
languages, and compiled languages.

**Interpreted languages** are languages like MATLAB and Python. When you
run a program written in one of these languages, your computer reads
through your source files (`.m`, `.py`), _interprets_ what each line means,
and then performs an action.

Intuitively, you can think of this as _your computer understanding what
the human-readable text of your program means,_ that is, the text `if`,
`then`, `else`, and `x = 4` are all things your computer can understand
without "translation."

**Compiled languages** are languages like C++. Before you can run
a program written in a compiled language, you first have to compile it with
a **compiler** (natch). This takes your source files (`.cpp`, `.hpp`) and
converts them into **machine code**, which is a set of very "low-level"
instructions that are meaningful to the underlying hardware (i.e. the
"silicon") of your computer.

Intuitively, you can think of this as _your computer only understanding
simple concepts, so that anything you tell your computer to do must be
broken down into small steps._

When you compile a C++ program into machine code, you get what's called a
**binary executable**, also called a **binary** (because the file is,
literally, raw binary) or an **executable** (because you can "execute",
i.e. run, the file and have it do useful things.) On Windows, binary
executables typically have the extension `.exe`. On Linux, they often don't
have a file extension.

(This is the reason why Linux operating systems like Ubuntu have a `/bin`
folder. On Ubuntu, `/bin` contains the binary executables for the programs
you've installed on that computer!)

Steps of the Compilation Process
--------------------------------------------------------------------------------
(Information taken from [thegeekstuff.com](https://goo.gl/fexQJk).)

There are four steps to the compilation process (important steps in bold):
1. **Pre-Processing**
  * Removal of commented code, execution of pre-processor directives (i.e.
    statements preceded with `#`).
2. Compilation
  * Conversion of human-readable source code into human-readable
  [assembly code](https://en.wikipedia.org/wiki/Assembly_language).
3. Assembly
  * Conversion of human-readable assembly code into machine-readable
    binary (i.e. machine code), with function calls not yet converted from
    their original plaintext.
4. **Linking**
  * Replacement of function call plaintext with a link to the corresponding
    function implementation.

We'll cover pre-processing and linking below.

### Pre-Processing


### Compiling Multiple Source Files
Most programs that actually see real-world use are much, much larger than a
single `.cpp` file. While it's theoretically possible for MAAV to, for
instance, compress the entirety of the `maav-vision` executable into one
file, this would quickly make the file almost impossible to maintain.

Any time you call g++, it produces one--and only one--C++ executable. The
executable can consist of multiple source files "linked" together.
