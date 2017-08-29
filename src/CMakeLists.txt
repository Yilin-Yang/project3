# TODO:
#	-Add the source (.cpp) files inside this folder to the `my-little-eigen` library.
#	-

find_package(Eigen3 REQUIRED)

# LEARN:	What does `SHARED` mean?
# See:		https://stackoverflow.com/questions/2649334/
#			`docs/build_systems.md`
add_library(my-little-eigen SHARED
	# ADD YOUR SOURCE FILES HERE
)
