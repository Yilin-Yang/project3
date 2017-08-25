#ifndef MAAV_PROJECT_3_ARRAY_2D_HPP
#define MAAV_PROJECT_3_ARRAY_2D_HPP

#include <cstdlib>	// size_t
#include <utility> 	// std::pair

/**
 * @brief Represents a two-dimensional array.
 * @author Your Name (youruniqname)
 * @detail Though C++ does natively support two-dimensional arrays, they're
 * 		less efficient than one-dimensional arrays in several ways.
 *
 *		2D C++ arrays are actually 1D arrays of pointers to 1D arrays of
 *		data values: the "row" is the specific 1D array of values you want to
 *		index, and the "column" is the value within that array that you want.
 *
 *		This leads to inefficiency.
 *
 *		All together, the "inner" arrays representing each row take up as much
 *		space as an equivalent 1D array containing all of the 2D array's
 *		elements. The "outer" array of pointers to those row arrays uses up
 *		`{NUM_ROWS}` additional bytes of memory on top of that. When working
 *		with very large arrays--or a very large number of small arrays--that
 *		wasted storage space is a major concern.
 *
 *		"Following" those pointers to the row arrays is also an operation that
 *		takes time. Again, this is negligible when working with small numbers
 *		of small arrays, but it could slow down program execution substantially
 *		when working with very large arrays or large numbers of small arrays.
 *
 *		Array2D internally represents a 2D array as a 1D array. Rather than
 *		an array of pointers to arrays, it is a single array whose row arrays
 *		are stuck together "end-to-end".
 *
 *		You can still index using (row, column). You just have to do math.
 *		These implementation details are hidden from the user (i.e. you, when
 *		you're implementing Matrix): if you get it all working here, you don't
 *		have to worry about any of those things while you're writing Matrix.
 */
class Array2D
{
	/**
	 * @brief Type alias for the container that represents an Array2D's size.
	 * @detail This is one of the ways to get around the prohibition on putting
	 * 		`using` statements in a header file.
	 *
	 * 		Because this `using` statement is located inside of Array2D, its
	 * 		scope only covers the Array2D class. That means that anybody who
	 * 		`include`s this header won't be able to use this type alias by
	 * 		accident.
	 *
	 * 		They also won't be able to use it on purpose
	 * 		(e.g. 'Array2D::SizePair`), because this alias isn't `public:`.
	 */
	using SizePair = std::pair<size_t, size_t>;

public:

	Array2D() = default;

	/**
	 * @brief Create a zero-initialized Array2D with the given size.
	 */
	Array2D(size_t num_rows, size_t num_cols);

	/**
	 * @addtogroup BIG_THREE The Big Three
	 * @brief You have to implement these when working with dynamic memory.
	 * @{
	 */

	/**
	 * @brief Deep-copy the elements of `to_copy` into a new `Array2D`.
	 * @detail This is a copy constructor.
	 *
	 * 		This is the constructor that allows you to:
	 * 		<ul>
	 * 		<li> Pass Array2D instances as function arguments that are not
	 * 			 `const ref`s
	 * 		<li> Directly construct Array2D's that are duplicates of another
	 * 			 Array2D by doing: `Array2D copy{another_array_2d};`
	 * 		</ul>
	 *
	 * 		The default (i.e. `... = default;`) copy constructor performs a
	 * 		"shallow copy". It takes the member variables of the other instance
	 * 		`to_copy` and copies all of its member variables into a new instance
	 * 		of that class.
	 *
	 * 		This is an issue if your class members include pointers.
	 * 		Copy-constructing a pointer gives you, in the end, _two_ pointers
	 * 		that point to the _same location in memory._
	 *
	 * 		This means that, if you were to use the default copy constructor
	 * 		with Array2D, modifications to the _copy_ of Array2D would also
	 * 		affect the original!
	 *
	 * 		You have to deep-copy `to_copy`'s elements instead.
	 *
	 * 		To do this, you have to allocate a new `contents` array for the new
	 * 		Array2D and copy over each element.
	 */
	Array2D(const Array2D& to_copy);

	/**
	 * @brief Assign the contents of `assign_from` to this Array2D.
	 * @detail This is an assignment operator.
	 *
	 * 		This is the function that allows you to do this:
	 * 				// ... code stuff ...
	 * 				Array2D an_array; // calls default constructor
	 * 				an_array = array_from_above; // declared somewhere above
	 *
	 * 		Which is functionally identical to:
	 * 				Array2D an_array = array_from_above;
	 *
	 * 		The default assignment operator performs a "shallow copy". See
	 * 		the documentation for Array2D's copy constructor for an explanation
	 * 		of why this is bad.
	 */
	Array2D& operator=(const Array2D& assign_from);

	/**
	 * @brief Destroy this Array2D.
	 * @detail This is a destructor.
	 *
	 * 		This is the function that gets called in situations like...
	 * 				delete ptr_to_dynamically_allocated_array2d;
	 *
	 * 		...or, more commonly, in situations like...
	 * 				void someFunction()
	 * 				{
	 *					Array2D an_array;
	 *
	 *					// do stuff with array
	 *
	 *					return;
	 * 				}
	 *
	 * 		...after you've hit the end of the function.
	 *
	 * 		`an_array` no longer exists once the function exits. C++ calls
	 * 		`delete` on the memory address of `an_array` once you've exited
	 * 		the body of that function.
	 *
	 *		The default destructor `delete`s each of Array2D's member variables.
	 *		If that member variable was a pointer to dynamically-allocated
	 *		memory, the `delete` destroys the pointer, but leaves all of that
	 *		memory still there.
	 *
	 *		This is what's called a memory leak.
	 */
	~Array2D();

	/**
	 * @}
	 */

	/**
	 * @brief Return the size of this Array as a `(num_rows, num_columns)` pair.
	 */
	const SizePair& size() const;

	/**
	 * @brief Allow modification of a specific element in this Array2D.
	 * @return A reference to the requested data element. This element can be
	 * 		modified, which will alter the contents of this Array2D.
	 */
	double& operator()(size_t row, size_t col);

	/**
	 * @brief Allow read-only access to a specific element in this Array2D.
	 * @return A copy of the value stored at the given index. Altering this
	 * 		element does not affect this Array2D, hence the `const` cv-qualifier
	 * 		at the end of this function header.
	 */
	double operator()(size_t row, size_t col) const;

	/**
	 * @brief Allow access to the "raw" array contained by this Array2D.
	 * @return A reference to the requested data element. This element can be
	 * 		modified, which will alter the contents of this Array2D.
	 */
	double& operator[](size_t index);

	/**
	 * @brief Allow read-only access to the underlying array.
	 * @return A copy of the value stored at the given index. Altering this
	 * 		element does not affect this Array2D, hence the `const` cv-qualifier
	 * 		at the end of this function header.
	 */
	double operator[](size_t index) const;

private:

	/**
	 * @addtogroup NO_CHANGE Can't Modify These Declarations
	 * @brief You aren't allowed to modify these variable declarations.
	 * @detail You will be manipulating the contents of these variables in
	 * 		your implementation of this class, but you aren't allowed to,
	 * 		say, replace the `unique_ptr` to an `Array2D` with an
	 * 		`Eigen::Matrix`.
	 * @{
	 */

		/**
		 * @brief A dynamically-allocated array holding this Array2D's contents.
		 */
		double* contents{nullptr};

		/**
		 * @brief The size of this matrix, given as a `(rows, columns)` pair.
		 * @detail Zero-initialized, representing an empty Array2D.
		 */
		SizePair array_size{0, 0};

	/**
	 * @}
	 */
};

#endif
