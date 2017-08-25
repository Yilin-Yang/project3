# LEARN:	What happens if you comment this out?
include_directories(
	${PROJECT_SOURCE_DIR}/src
)

#---------------------------------------------------------------------
# Lists in CMake
#---------------------------------------------------------------------
# From StackOverflow:
#		Lists in CMake are just strings with semicolons delimiters and
#		therefore the quotation-marks are important.
#			set(MyVar a b c) is "a;b;c" and set(MyVar "a b c") is "a b c"
#
#		The recommendation is that you always use quotation marks with the one
#		exception [being] when you want to give a list as list.
#
#		[In general, you should] prefer the list() command for handling lists.
#
# Note that, in CMake, *every* variable is internally represented as a string.
#---------------------------------------------------------------------
# See:
#	https://stackoverflow.com/questions/31037882/
#---------------------------------------------------------------------
set(test_files
	Array2DPublicTest
	MatrixPublicTest
#		ADD YOUR TEST CASE FILES HERE
)

# LEARN:	what does the "foreach" command do?
foreach(test_name ${test_files})
	# LEARN:	Is the ".exe" strictly necessary? What happens if you change
	#			it to something else?
	set(curr_executable "${test_name}.exe")

	add_executable(${curr_executable} ${curr_executable}.cpp)

	target_link_libraries(${curr_executable}
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
		#	LINK THE LIBRARY YOU CREATED IN `./src/CMakeLists.txt`
	)

	add_test(
		NAME 		${test_name}
		COMMAND 	${curr_executable}
	)
# LEARN:	Which of the following are valid ways to format
#			the command above?
#			1)	aDd_TeSt(name ${test_name} command ${curr_executable})
#			2)	add_test(NAME ${test_name} COMMAND ${curr_executable})
#			3)	add_test(NAME "${test_name}" COMMAND "${curr_executable}")
#			4)	add_test(NAME, ${test_name}, COMMAND, ${curr_executable})
#			5)	add_test(NAME
#				${test_name}
#					COMMAND
#
#								${curr_executable}
#				)
endforeach()
