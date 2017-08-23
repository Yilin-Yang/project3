To clone this project, run the command:

		git clone https://github.com/maavumich/project3

...in a terminal. This will create a directory in the present working
directory ("`PWD`") called `project3` that contains all of the files in
this repo.

# Training Project 3

Pointers, references, operator overloading, build systems, test-driven
development, and the Big Three. Three-indexed (fourth) project in the core
training sequence.

Trainees will implement a `Matrix` class supporting basic matrix
operations. Trainees will make use of test-driven development and practice
working with some of the libraries and systems used by MAAV software
developers.

Instructions and pass requirements are found in the `./docs` folder.

**To jump to a file in vim, move your terminal cursor over the file or
directory in normal mode and type** `gf`.

**Type** `CTRL-^` **in normal mode to return to the previously-opened file.**

**See** `./docs/navigating_buffers.md` **for more information.**

## Topics Covered

* Pointers
	* C-style pointers
	* C++ smart pointers
	* References
* Dynamic memory allocation / the "Big Three"
	* The `new` keyword
	* Deleting dynamically-allocated objects
	* Deleting dynamically-allocated arrays
	* Debugging memory leaks using valgrind
* Overloading `operator`s
* The CMake build system
* Linking source files to external libraries
* Test-driven development; Boost Test Cases


## Directory Structure

### Documentation 			[`./docs`]

The project spec, as well as informational resources on the topics covered
by this project.

Contains:
* The assignment, in detail (`./docs/assignment.md`)
* Grading information (`./docs/grading.md`)
* How to more easily navigate the project's documentation files in vim
  (`./docs/navigating_buffers.md`)
* Notes and informational resources on all of the topics listed above
  (`./docs/notes.md`).

### Source					[`./src`]

Project source files, containing the bulk of `project3`'s implementation.

Contains:
* Starter files
	* `./src/2DArray.hpp`
	* `./src/Matrix.hpp`
	* `./src/CMakeLists.txt`

### Executables/Binaries	[`./bin`]

A source file for an executable that runs your code. Not necessarily the same
as the executable used to grade `project3` submissions.

Contains:
* `./bin/maav-equation-solver.cpp`

### Tests					[`./tests`]

Test cases for trainees' project implementation in `./src`.

Contains:
* Starter files
	* `./tests/2DArrayPublicTest.cpp`
	* `./tests/MatrixPublicTest.cpp`
	* `./tests/CMakeLists.txt`

### Potentially Useful		[`./maybe_useful`]

Things that trainees might find helpful.

Contains:
* `./maybe_useful/vimscript.md`
* `./maybe_useful/functions.vim`
* `./maybe_useful/install_dependencies.sh`
* `./maybe_useful/Makefile`
