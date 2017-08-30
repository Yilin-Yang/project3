#-------------------------------------------------------------------------------
# This file is xbox-hueg because of all the added comments and instructional
# information.
#
# See `./maybe_useful/CMakeLists.txt` to see what this file would "normally"
# look like.
#-------------------------------------------------------------------------------


#===============================================================================
#	CREATE A CMAKE PROJECT
#-------------------------------------------------------------------------------
#		Things you have to have in the root folder CMakeLists.txt.
#===============================================================================
cmake_minimum_required(VERSION 2.8)	# throws annoying warnings when not present
project(project3)					# the name of the project

# Tell CMake where it can find its `.cmake` files.
#	Usually, these are just scripts telling CMake where to find certain
#	libraries.

# (^That directory is empty/doesn't exist, since CMake can find Eigen3 and Boost
#  without any issues. This is necessary if you're using libraries that CMake
#  can't find in the usual places.)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")
#   ^ Set this variable to...
#                      ^ ...the current value of CMAKE_MODULE_PATH...
#                                          ^ ...and concatenate the
#                                          `./cmake` folder onto the *end*.
#______________________________________________________________________________




#===============================================================================
#	SET SOME BUILD OPTIONS AS CMAKE VARIABLES
#-------------------------------------------------------------------------------
#		Create some options that can be toggled in `ccmake`, or with
#		`-DSOME_OPTION=ON`.
#		  ^ no space between this `-D` flag and the option to follow
#===============================================================================

  #---------------------------------------------------------------------
  # CMake Variables
  #---------------------------------------------------------------------
  # From CMake's documentation,
  #		Variables are the basic unit of storage in the CMake Language.
  #		Their values are always of string type, though some commands may
  #		interpret the strings as values of other types.
  #
  #		The `set()` and `unset()` commands explicitly set or unset a variable,
  #		but other commands have semantics that modify variables as well.
  #
  #		Variable names are case-sensitive and may consist of almost any text,
  #		but we recommend sticking to names consisting only of alphanumeric
  #		characters plus '_' and '-'.
  #---------------------------------------------------------------------
  # See:
  #	https://stackoverflow.com/questions/35023939/cmake-variable-names-case-sensitive
  #	https://cmake.org/cmake/help/v3.4/manual/cmake-language.7.html#variables
  #---------------------------------------------------------------------

  # Add an option for building test cases.
  option(BUILD_TESTS "Compile test case executables." ON)
  #      ^ Sets this variable to a value...
  #                            ...that defaults to ON. ^
  #	Ordinarily this would default to OFF, since building test cases takes
  #	extra time even if the test cases source files haven't changed.



  # Add an option for compiling with -g.
  #	The `-g` flag tells the g++ compiler that it shouldn't optimize your code
  #	as it compiles; instead, it compiles your code "as-is" and leaves debugging
  #	symbols in the compiled executable.
  #
  #	Debugging symbols include, among other things, line numbers and the
  #	original code itself. Debuggers--like GDB--can find these symbols.
  #	This makes it possible for you to set breakpoints (i.e. "pause"
  #	program execution at a specific line in a specific file), step through
  #	your code line-by-line, and print variable values as the program runs
  #	without having to add `std::cout` or `printf` statements everywhere
  #	in the source files.
  option(BUILD_WITH_DEBUG_SYMBOLS "Add debugging information to executables." ON)

  if (BUILD_WITH_DEBUG_SYMBOLS)
  # ^ Whitespace *in and around* parentheses is optional in CMake.
  # 	`if(BUILD_WITH_...)` also works.
  	set(CMAKE_BUILD_TYPE "Debug")
  else()
  	set(CMAKE_BUILD_TYPE "Release")
  endif()
  #    ^ You don't have to have anything between these parentheses, but you do
  #    have to have these parentheses here.
  #
  #    Ditto for `else()`.
#______________________________________________________________________________


#===============================================================================
#	SET COMPILER FLAGS
#-------------------------------------------------------------------------------
#		Set additional flags to pass to g++ when asking it to compile our code.
#===============================================================================
message("Prior to calling `set`, our compiler flags are:" ${CMAKE_CXX_FLAGS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#                    ^ Again, we're appending values to existing variables.

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")

message("Afterwards, our compiler flags are:" ${CMAKE_CXX_FLAGS})

#-------------------------------------------------------------------------------
# Q:	Do we have to do this again in `./src` or `./bin`?
#-------------------------------------------------------------------------------
# A:	You do not! CMake variables have a dynamic scope and are accessible
#		in all CMakeLists.txt files "beneath" the file where they were declared.
#
#		See `./docs/cmake.md` for more details!
#-------------------------------------------------------------------------------

#______________________________________________________________________________

#===============================================================================
#	ADD SOURCE FOLDER AND BINARIES FOLDER
#-------------------------------------------------------------------------------
#		Have CMake generate Makefiles for the `./src` and `./bin` folder.
#
#		****You have to do this yourself.****
#		Feel free to use the rest of this file as a reference for CMake
#		syntax.
#
#		(Also, give CMake the list of directories to pass to g++ in '-I' flags.)
#===============================================================================
#*******************************************************************************
#*******************************************************************************
#		YOUR IMPLEMENTATION HERE
#*******************************************************************************
#*******************************************************************************

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#______________________________________________________________________________


#===============================================================================
#	INCLUDE SOURCE FOLDER AND BINARIES FOLDER
#-------------------------------------------------------------------------------
#
#===============================================================================

#______________________________________________________________________________


#===============================================================================
#	TEST CASE STUFF
#-------------------------------------------------------------------------------
#		Have CMake generate Makefiles for the `./tests` directory, if
#		BUILD_TESTS was set to ON.
#===============================================================================

  #---------------------------------------------------------------------
  # find_package(...)
  #---------------------------------------------------------------------
  # From CMake's documentation,
  #		CMake searches for a file called Find<package>.cmake in the
  #		CMAKE_MODULE_PATH followed by the CMake installation. If the file is
  #		found, it is read and processed by CMake. It is responsible for finding
  #		the package, checking the version, and producing any needed messages.
  #
  #---------------------------------------------------------------------
  # See:
  #	https://cmake.org/cmake/help/v3.0/command/find_package.html
  #---------------------------------------------------------------------
  fInD_pAcKaGe(Boost COMPONENTS unit_test_framework REQUIRED)
  # Note:
  #        ^ case-insensitive
  #            ^ case-sensitive
  #                  ^ case-sensitive

  #---------------------------------------------------------------------
  # CTest
  #---------------------------------------------------------------------
  # From CMake's documentation,
  #
  #		CMake has support for adding tests to a project:
  #		   enable_testing()
  #
  #		This adds another build target, which is test for Makefile
  #		generators, or RUN_TESTS for integrated development environments
  #		(like Visual Studio).
  #
  #		From that point on, you can use the ADD_TEST command to add tests
  #		to the project:
  #		   add_test( testname Exename arg1 arg2 ... )
  #
  #		Or, in its longer form:
  #		   add_test(NAME <name> [CONFIGURATIONS [Debug|Release|...]]
  #		            [WORKING_DIRECTORY dir]
  #		            COMMAND <command> [arg1 [arg2 ...]])
  #
  #		Once you have built the project, you can execute all tests via
  #		    make test
  #
  #		with Makefile generators, or by rebuilding the RUN_TESTS target in
  #		your IDE. Internally this runs CTest to actually perform the
  #		testing; you could just as well execute
  #		    ctest
  #
  #		in the binary directory of your build.
  #---------------------------------------------------------------------
  # See:
  #	https://cmake.org/Wiki/CMake/Testing_With_CTest
  #	`./docs/cmake.md`
  #	`./docs/test_driven_development.md`
  #	`./docs/boost_test_cases.md`
  #---------------------------------------------------------------------------
  if (BUILD_TESTS)
  	enable_testing()
  	add_subdirectory(tests)
  endif()
