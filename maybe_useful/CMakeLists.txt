# The root-level CMakeLists.txt, without comments, debug print statements,
# and other formatting (except for this, obviously).
#
# This is provided as a reference for what a "normal" CMakeLists.txt would
# look like.

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

option(BUILD_TESTS "Compile test case executables." ON)
option(BUILD_WITH_DEBUG_SYMBOLS "Add debugging information to executables." ON)

if (BUILD_WITH_DEBUG_SYMBOLS)
	set(CMAKE_BUILD_TYPE "Debug")
else()
	set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")

add_subdirectory(nergle)
add_subdirectory(blergle)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

if (BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()
