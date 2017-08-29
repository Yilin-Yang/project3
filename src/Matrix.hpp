#ifndef MAAV_PROJECT_3_MATRIX_HPP
#define MAAV_PROJECT_3_MATRIX_HPP

#include "Array2D.hpp"

#include <iostream>	// std::ostream
#include <memory>	// std::unique_ptr

/**
 * @brief Represents a two-dimensional matrix, to be used for linear algebra.
 * @author Your Name (youruniqname)
 * @detail Matrix is, essentially, a simplified version of an `Eigen::Matrix`.
 * 		It's capable of element-wise arithmetic, supports basic matrix math
 * 		operations, and has a few utility functions to make it easier to use.
 *
 * 		Matrix "has-a(n)" Array2D that acts as its internal representation
 * 		of its contents. This is hidden from the user (i.e. us, when we're
 * 		writing executables to test your code, and you, when you're writing
 * 		your test cases).
 *
 * 		In the real world, you could change this to something else (maybe you
 * 		want to just use a native 2D array for sake of simplicity), and as long
 * 		as you **don't change the public interface** (i.e. as long as row-column
 * 		indexing still returns the element at the correct row and column, and
 * 		so on), none of the code that uses `Matrix` would have to change.
 *
 * 		(They'll spend a few lectures talking about that in EECS280. This
 * 		concept is called **procedural abstraction**.)
 *
 * 		Note that **all of the methods below** should throw
 * 		`std::runtime_error`s if invoked upon a "blank" matrix (i.e. a
 * 		matrix whose `contents` pointer is a `nullptr`).
 */
class Matrix
{

	using SizePair = std::pair<size_t, size_t>;

public:

	/**
	 * @brief Create a "blank" Matrix.
	 * @detail This "explicitly defaults" Matrix's default constructor.
	 */
	Matrix() = default;

	/**
	 * @brief Create a zero-initialized Matrix with the given size.
	 * @detail `size_t` is an unsigned integer type. The `.size()` on
	 * 		standard library containers return `size_t` values. Ordinarily,
	 * 		it's an alias for `unsigned long int`, i.e. a 64-bit unsigned
	 * 		integer.
	 *
	 * 		Zero-initialization means that every element of this Matrix will
	 * 		have a starting value of zero.
	 */
	Matrix(size_t num_rows, size_t num_cols);

	/**
	 * @addtogroup BIG_THREE The Big Three
	 * @brief You have to implement these when working with dynamic memory.
	 * @detail **LEARN:** Would you still have to implement this if Matrix
	 * 		"had-an" Array2D object rather than a pointer to an Array2D that
	 * 		exists on the heap?
	 * @{
	 */

		/**
		 * @brief Deep-copy the members of `to_copy` into a new Matrix.
		 * @detail See the copy constructor for Array2D--as well as the
		 * 		project documentation--for more information on copy
		 * 		construction.
		 */
		Matrix(const Matrix& to_copy);

		/**
		 * @brief Assign the contents of `assign_from` into this Matrix.
		 * @detail See the assignment operator for Array2D--as well as the
		 * 		project documentation--for more information on what the
		 * 		assignment operator does and needs to do.
		 */
		Matrix& operator=(const Matrix& assign_from);

		/**
		 * @brief Destroy this Matrix.
		 * @detail See the destructor for Array2D, as well as the project
		 * 		documentation--for more information on the destructor does/needs
		 * 		to do.
		 */
		~Matrix();

	/**
	 * @}
	 */

	/**
	 * @addtogroup ACCESSORS Accessor Functions
	 * @brief Function for getting or modifying Matrix members.
	 * @{
	 */

		/**
	 	 * @brief Return this Matrix's size as a `(num_rows, num_columns)` pair.
		 */
		const SizePair& size() const;

		/**
	 	 * @brief Allow modificiation of a specific element in this Matrix.
		 */
		double& operator()(size_t row, size_t col);

		/**
	 	 * @brief Allow read-only access to a specific element in this Matrix.
		 */
		double operator()(size_t row, size_t col) const;

	/**
	 * @}
	 */

	/**
	 * @brief Resize this Matrix to have the given number of rows and columns.
	 * @return A reference to this matrix (i.e. a dereferenced `this`
	 * 		pointer, obtained with `(*this)`).
	 * @detail If the matrix is being shrunk, shrink from the bottom-up
	 * 		(for rows) and from right-to-left (for columns). This discards
	 * 		the contents of those rows and columns.
	 *
	 * 		If the matrix is being enlarged, zero-initialize the new rows
	 * 		and columns.
	 *
	 * 		Note that, in order to do this, you have to manipulate the
	 * 		`contents` `Array2D` storing
	 */
	Matrix& resize(size_t num_rows, size_t num_cols);

	/**
	 * @brief Return the element-wise sum of this Matrix with the other.
	 * @detail Checks whether the matrices have the same size. Throws an
	 * 		exception (`std::runtime_error`) if the sizes do not match.
	 *
	 * 		Passing the following two 2x2 matrices...
	 * 				[1	2]		[5	6]
	 * 				[3	4]		[7	8]
	 *
	 *		...into this function returns the following matrix:
	 *				[6	8 ]
	 *				[10	12]
	 *
	 * 		To call this function with `Matrix firstMat` and
	 * 		`Matrix secondMat` as arguments, do:
	 * 				Matrix outputMat = firstMat + secondMat;
	 *
	 * 		You are overriding the addition operator.
	 */
	Matrix operator+(const Matrix& rhs) const;

	/**
	 * @brief Return the element-wise difference of this Matrix with the other.
	 * @detail Checks whether the matrices have the same size. Throws an
	 * 		exception (`std::runtime_error`) if the sizes do not match.
	 *
	 * 		Passing the following two 2x2 matrices...
	 * 				[1	2]		[5	6]
	 * 				[3	4]		[7	8]
	 *
	 *		...into this function returns the following matrix:
	 *				[-4	-4]
	 *				[-4	-4]
	 *
	 * 		To call this function with `Matrix firstMat` and
	 * 		`Matrix secondMat` as arguments, do:
	 * 				Matrix outputMat = firstMat - secondMat;
	 *
	 * 		You are overriding the subtraction operator.
	 */
	Matrix operator-(const Matrix& rhs) const;

	/**
	 * @brief Return the matrix-product of these two matrices.
	 * @detail Checks whether the matrices are appropriately sized. Throws an
	 * 		exception (`std::runtime_error`) if the sizes are not valid.
	 *
	 * 		Passing the following two matrices...
	 * 				[1	2]		[7	8 ]
	 * 				[3	4]		[9	10]
	 * 				[5	6]
	 *
	 *		...into this function returns the following matrix:
	 *				[25	28 ]
	 *				[57	64 ]
	 *				[89	100]
	 *
	 * 		To call this function with `Matrix firstMat` and
	 * 		`Matrix secondMat` as arguments, do:
	 * 				Matrix outputMat = firstMat * secondMat;
	 *
	 * 		You are overriding the multiplication operator.
	 *
	 * 		For more details on matrix multiplication, use the following
	 * 		link, reference lecture material, ask a MAAV member for help,
	 * 		or search for additional resources on Google.
	 *
	 * 		[Tutorial](https://www.mathsisfun.com/algebra/matrix-multiplying.html)
	 */
	Matrix operator*(const Matrix& rhs) const;

	/**
	 * @brief Divide this matrix by a scalar and return the quotient.
	 * @detail Passing the following two arguments...
	 * 				[1	2]		2.0
	 * 				[3	4]
	 *
	 * 			...into this function returns the following matrix.
	 * 				[0.5	1.0]
	 * 				[1.5	2.0]
	 */
	Matrix operator/(double divisor) const;

	/**
	 * @brief Return the element-wise quotient of this Matrix with the other.
	 * @detail Checks whether the matrices have the same size. Throws an
	 * 		exception (`std::runtime_error`) if the sizes do not match.
	 *
	 * 		Passing the following two 2x2 matrices...
	 * 				[1	2]		[5	6]
	 * 				[3	4]		[7	8]
	 *
	 *		...into this function returns the following matrix:
	 *				[0.2	0.333]
	 *				[0.429	0.5  ]
	 *
	 * 		To call this function with `Matrix firstMat` and
	 * 		`Matrix secondMat` as arguments, do:
	 * 				Matrix outputMat = firstMat.divide(secondMat);
	 *
	 * 		Matrix division is not a well-defined operation. In some
	 * 		contexts, it refers to finding the inverse of a matrix (`A^1`) and
	 * 		then multiplying by that inverse (`X * A^1`); other times, it
	 * 		refers to element-wise division.
	 */
	Matrix divide(const Matrix& rhs) const;

	/**
	 * @brief Return the inverse of this matrix.
	 * @detail If the matrix is not invertible (i.e. isn't square), throw
	 * 		an (`std::runtime_error`).
	 *
	 * 		The inverse of the 1x1 matrix...
	 * 				[x]
	 *
	 *		...is the 1x1 matrix:
	 *				[1/x]
	 *
	 *		The inverse of the 2x2 matrix...
	 *				[a	b]
	 *				[c	d]
	 *
	 *		...is given by:
	 *				(1 / (ad - bc))	*	[ d	-b]
	 *									[-a	 c]
	 *
	 *		**For this function,** you don't need to handle matrices larger
	 *		than 2x2.
	 */
	Matrix inverse() const;

	/**
	 * @brief Return the transpose of this matrix.
	 * @detail Return a copy of this matrix, with every element "flipped"
	 * 		over a diagonal line running from the top-left of the matrix to
	 * 		its bottom-right.
	 *
	 * 		That is, "the rows become columns, and the columns become rows."
	 *
	 *		The transpose of the 3x2 matrix `A` (normally denoted `A'`) is
	 *		given by:
	 *
	 *				[a	b]'				[a	c	e]
	 *				[c	d]		=		[b	d	f]
	 *				[e	f]
	 *
	 *		A "double transpose" (`A''`) is identical to the original
	 *		matrix (`A'' == A`).
	 */
	Matrix transpose() const;

	/**
	 * @brief Return true when this and the other matrix are equal.
	 */
	bool operator==(const Matrix& rhs) const;

	/**
	 * @brief Return true when this and the other matrix are not equal.
	 */
	bool operator!=(const Matrix& rhs) const;

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
		 * @brief The contents of this matrix as a dynamically-allocated array.
		 */
		std::unique_ptr<Array2D> contents;

	/**
	 * @}
	 */

};

/**
 * @brief Insert the matrix into the given output stream.
 * @detail Given a matrix `A`...
 * 				[1	2]
 * 				[3	4]
 *
 *		...the function call...
 *				std::cout << A << std::endl;
 *
 *		...would print...
 * 				[1	2]
 * 				[3	4]
 *
 * 		...to the terminal window. The closing bracket (`]`) is followed
 * 		by _one_ newline character.
 *
 * 		If this call is followed by:
 * 				std::cout << "foobar" << std::endl;
 *
 * 		...the terminal would display:
 * 				[1	2]
 * 				[3	4]
 * 				foobar
 */
std::ostream& operator<<(std::ostream& os, const Matrix& mat);

#endif
