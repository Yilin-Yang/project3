# Project Specification

# Your Goal

## Figure Out How Dynamic Memory Works
See `./dynamic_memory.md`.

## Implement Source Files
You must write implementations for each of the functions declared in
both `Matrix.hpp` and `Array2D.hpp` in the source files `Matrix.cpp` and
`Array2D`, respectively.

### The Files Themselves
Further explanation of what these classes are--and hints on how they should
be implemented-- are given below.

Further detailed infrmation about `Matrix` and `Array2D` is given in the
`@detail` in their respective header (`hpp`) files.

#### Array2D

**How do arrays work in C++?**
See `./containers.md`.

**Why have an Array2D type?**
**TODO: explain why**

**Why use native arrays?**
For this project, you will work with native arrays (i.e. you will not be
using `std::array` or `std::vector`). The reasons for this are that it:
* Forces you to "do the dirty work" that would be involved with actually
  writing a class like `std::vector`.
* Lets us force you to practice using dynamic memory.
* Makes your code more efficient (i.e. faster and using less memory) than using
  other container types, _if_ you implement your code well.


#### Matrix

**What's the point of smart pointers?**
**TODO: explain why**

**Hints**
Resizing a Matrix is an expensive operation.

You aren't allowed to "stick more memory" onto the end of the memory chunk
allocated to `Matrix`'s `Array2D`. You have no guarantee that the space
after that chunk isn't being used for something else. If you tried to do
this anyways, the program that you write would corrupt its allocated memory
and crash if allowed to run for too long.

For the purposes of this project, you should:
* Create a new `Array2D` that's large enough to hold the elements that you
  need.
* Copy over as many elements as you can (and zero-initialize the remainder,
  if you're making the `Array2D` larger).
* `delete` the original Array2D.
* Assign a pointer to the new `Array2D` to `contents`.

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


## Write Test Cases
**TODO: Explanation of test-driven development.**

**TODO: link to Boost test cases Markdown file**

### CMakeLists
**TODO: src folder, bin folder, tests folder**


## Caveats (i.e. "You Don't Have To Worry About...")
* For certain functions (e.g. `inverse()`), you may assume that you will never be
  given a matrix larger than 2x2.
  * While doing work for MAAV, you will probably--eventually--be given
	tasks that are as complex as implementing, for instance, a matrix
	`inverse()` operation for an NxN matrix (though you won't be given that
	task specifically, since that's already handled in the Eigen library.)
  * The purpose of this project is to introduce the topics described in the
	README, not to be a comprehensive tutorial on linear algebra, or to
	"weed out the weak."
* Your implementation code does not have to accommodate systems of
  equations with no unique solution.
