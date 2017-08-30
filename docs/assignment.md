Project Specification
================================================================================

Things You Need To Do
================================================================================

Figure Out How Dynamic Memory Works
--------------------------------------------------------------------------------
Ordinarily, the lifetime of an object is managed for you by C++. Global
variables live until the end of program execution, local variables are
destroyed at the end of the function in which they were declared, and class
member variables are destroyed when the instance they belong to is
destroyed.

Sometimes, you might want to manage an object's lifetime yourself. Or, you
might want to make heavy use of polymorphism, which is difficult (though
not impossible) without the use of dynamic memory. Or maybe you're just
working with massive data objects (like entire pictures or large videos)
that are, quite literally, too large to create and work with in the "usual
way".

This project forces you to do work with one of the smaller, more mundane
things that requires the use of dynamic memory: namely, creating native
arrays whose size is not necessarily known at compile time.

See `./dynamic_memory.md` for more information.


Figure Out How CMake Works
--------------------------------------------------------------------------------
As you've probably come to realize, compiling several C++ source files by
manually typing in `g++` commands is tedious and error-prone. Makefiles are
a good solution when working with small projects, but even they aren't
adequate when working with a large codebase.

CMake is an open-source build system. It has its own scripting language
that lets you define exactly how you want your project to be compiled
and tools for translating those scripts into Makefiles.

You probably won't work on any programming projects for your classes large
enough to require CMake until your junior or senior year, but when you do,
knowing CMake will make you a godsend to whatever group you wind up working
with.

As you've seen in Project 2, the MAAV codebase uses CMake as its build
system. If you start playing around with open source software, you'll find
that many of them use CMake as well.

See `./cmake.md` for more information.


Implement Source Files
--------------------------------------------------------------------------------
You must write implementations for each of the functions declared in
both `Matrix.hpp` and `Array2D.hpp` in the source files `Matrix.cpp` and
`Array2D`, respectively.

### The Files Themselves
Further explanation of what these classes are--and hints on how they should
be implemented-- are given below.

Further detailed infrmation about `Matrix` and `Array2D` is given in the
`@detail` in their respective header (`hpp`) files.


#### Array2D
`Array2D` "is" a two-dimensional array; it lets its user index into a given cell
with a row number and a column number, Internally, it's a one-dimensional
array "pretending" to be a two-dimensional array.

##### TODO
* **Implement all of the functions in `src/Array2D.cpp`.
* Add `Array2D` to the `my-little-eigen` library using CMake.
* Write test cases for `Array2D` in `tests` to make sure that it works as
  expected.
* Run your `Array2D` test cases in valgrind to make sure you don't have any
  memory leaks.**

##### How do native arrays work in C++?
See `./containers.md`.

##### Why use native arrays?
For this project, you will work with native arrays (i.e. you will not be
using `std::array` or `std::vector`). The reasons for this are that it:
* Forces you to "do the dirty work" that would be involved with actually
  writing a class like `std::vector`.
* Lets us force you to practice using dynamic memory.
* Makes your code more efficient (i.e. faster and using less memory) than using
  other container types, _if_ you implement your code well.

##### Why not use a native 2D array?
NOTE: A native 2D array is a native array of pointers to other native
arrays, such as:
		int array_2d[2] = {int[2], int[2]};

The short answer is that "real" two-dimensional arrays are less efficient--in
memory usage and in execution time--than one-dimensional arrays pretending
to be two-dimensional arrays.

##### How do you index into a 1D array using only a row and a column?
With math!

Here's a hint. Imagine that each row in the "2D" array is laid end-to-end.
How would you find the start of the third row? How would you find the third
element within that row?


#### Matrix
`Matrix` represents a mathematical matrix, as they're used in linear algebra.
It has functions allowing it to be added, subtracted, matrix-multiplied,
scalar-multiplied, transposed, and so on. For sake of simplicity, you'll only
be implementing simple matrix operations for this project.

`Matrix` possesses a "has-a" relationship with `Array2D`. It stores its
elements using the `Array2D` data structure, and its functions for
"getting" elements just call the equivalent methods in `Array2D`.

Unlike `Array2D`, `Matrix` _is resizeable_. It does this by copying all of
its current elements into another `Array2D`, `delete`ing its current
`Array2D`, and using the new `Array2D` for element storage.

To do this, you should:
* Create a new `Array2D` that's large enough to hold the elements that you
  need.
* Copy over as many elements as you can (and zero-initialize the remainder,
  if you're making the `Array2D` larger).
* `delete` the original Array2D.
* Assign a pointer to the new `Array2D` to `contents`.

##### TODO
* **Implement all of the functions in `src/Matrix.cpp`.
* Add `Matrix` to the `my-little-eigen` library using CMake.
* Write test cases for `Matrix` in `tests` to make sure that it works as
  expected.
* Run your `Matrix` test cases in valgrind to make sure you don't have any
  memory leaks.**

### Restrictions/Suggestions
The following applies to all of the project's source files.

#### You Cannot...
...change the public interface of your files. This means that you can't:
* Add new public functions.
* Change the signature of the functions declared in `Matrix.hpp` or
  `Array2D.hpp`.
* Change any private variables that were already declared in `Matrix.hpp` or
  `Array2D.hpp`.
* Add public member variables. (This is almost always considered bad practice,
  anyhow, unless the class that you're writing is "plain old data.")

#### You May/Should...
* Write private functions to break down the implementation of the public
  functions into smaller chunks.
* Add private member variables, if you think it'll be helpful.
* Write test cases _before_ writing your function implementations, or write
  them side-by-side with your function implementations.


Write Test Cases
--------------------------------------------------------------------------------
You won't be given access to this project's autograder. This is meant to
replicate the experience of writing real code for MAAV.

When you're writing the quadcopter's path planning code, you won't have an
answer key or an autograder. A failing grade isn't a D- on Wolverine
Access; a failing grade is taking the quadcopter to Willow Run Airport for
flight testing and watching it sail directly into a spinning jet turbine.

There are countless issues--both with hardware and with software--that
could cause something like that to happen. Oftentimes, it won't be
something dramatic; it'll be something small and stupid that _would have
been caught with adequate unit testing._

Let's say you accidentally read past the end of a native array. The memory
chunk directly after your array is OS-protected memory, so your program
doesn't have access to it. Your code segfaults. The entire executable in
which your code was written (in this example, `maav-planner`) crashes. Left
without a "brain", the quadcopter meanders about the hanger, then crashes
directly into Yilin's face. Yilin becomes sad.

To prevent this sort of thing from happening, you'll write test cases to
make sure that your code works the way it's supposed to. It's almost
guaranteed that you'll have to do this in the real world.

Some open-source projects that write test cases for their code include:
* [BulletPhysics](https://github.com/bulletphysics/bullet3/tree/master/test)
* [OpenCV](https://github.com/opencv/opencv/blob/master/cmake/templates/opencv_run_all_tests_unix.sh.in)
* [The Linux Kernel](https://github.com/torvalds/linux/tree/master/tools/testing)

You'll also have to write test cases for your EECS280 projects, if you
haven't taken it already, so you might as well learn now.

See `./test_driven_development.md` and `./boost_test_cases.md` for more
information.

##### TODO
* **Learn how to write Boost Test Cases.
* Write your test cases in the `tests` folder.
* Link the `my-little-eigen` library to the test case executables.
* Compile and run those tests using the CMake build system.**

Link the Binary
--------------------------------------------------------------------------------
A (very basic) systems test of your `Array2D` and `Matrix` code can be
found in the `bin` folder. It's an executable called
`maav-equation-solver`.

`maav-equation-solver` is already fully implemented. The only thing you
need to do is write its `CMakeLists.txt` file.

##### TODO
* **Link the `my-little-eigen` library to `maav-equation-solver`.
* Include the `src` folder, so that `maav-equation-solver` can `#include`
  your headers.
* Run `maav-equation-solver` and see if you're getting the right answers.**

Submit Your Code
--------------------------------------------------------------------------------
Submission method to be determined.


Final Notes
================================================================================

### The Matrix class isn't as difficult to write as it could be.
For certain functions (e.g. `inverse()`), you may assume that you will never be
given a matrix larger than 2x2.

While doing work for MAAV, you will probably--eventually--be given tasks
that are as complex as implementing  a matrix `inverse()` operation for an
NxN matrix (though you won't be given that task specifically, since that's
already handled in the Eigen library.)

### This isn't meant to be a comprehensive tutorial on linear algebra.
The purpose of this project is to introduce the topics described in the
README, not to be a comprehensive tutorial on linear algebra, or to "weed
out the weak."

### This project covers, like, four or five weeks worth of EECS280 at once.
Depending on how much prior coding experience you have, this project might
seem simple, or it might seem daunting.

If it seems simple, fantastic! If it seems terrifyingly complex, don't
fret too much. Many of the systems that MAAV's software teams _have_ to be
written by team members with multiple 400- and 500-level computer science
courses under their belt. We hope that you can learn enough to work with
those systems anyhow, but we don't realistically expect you to do that
right away.

None of this means that it's impossible for a first- or second-year student
to learn enough to be able to make meaningful contributions to the
codebase. None of this means that you'll be asked to twiddle your thumbs
and watch while all the team veterans do all of the cool stuff.

The MAAV codebase is a jigsaw puzzle whose pieces haven't been cut from the
wood. Those pieces are numerous, heavily interrelated, and massively
complicated in and of themselves.

You and your future subgroup teammates will be asked to build _one_ of
those jigsaw pieces and fit it into the larger puzzle, doing the best job
that you reasonably can.


Appendix
================================================================================

### How to Throw An `std::runtime_error`

Example Usage:
		#include <exception>

		//...

		double divide(double lhs, double rhs)
		{
			if (rhs == 0)
			{
				throw std::runtime_error{"Division by zero!"};
			}
			return lhs / rhs;
		}

		//...

		int main()
		{
			divide(5.0, 0);
			std::cout << "Program finished execution." << std::endl;
			return 0;
		}

Output:
		terminate called after throwing an instance of 'std::runtime_error'
		  what():  Division by zero!
		Aborted (core dumped)

### How to Catch an `std::runtime_error`

Example Usage
		double divide(double lhs, double rhs)
		{
			// same as above
		}

		int main()
		{
			try
			{
				divide(5.0, 0);
			}
			catch (std::runtime_error)
			{
				std::cerr << "I dun goofed!\n";
			}
			std::cout << "Program finished execution." << std::endl;
			return 0;
		}

Output:
		I dun goofed!
		Program finished execution.
