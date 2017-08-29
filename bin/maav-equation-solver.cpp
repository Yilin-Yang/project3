#include "Matrix.hpp"
#include "Helpers.hpp"

#include <functional>
#include <iostream>

using std::cout;
using std::endl;
using std::function;

void runTest(function<bool(void)> test_function);
bool solveEquationOne();
bool solveEquationTwo();
bool solveEquationThree();
bool solveEquationFour();

int main()
{
	runTest(solveEquationOne);
	runTest(solveEquationTwo);
	runTest(solveEquationThree);
	runTest(solveEquationFour);
}

/**
 * @brief Run a test function and report success or failure.
 * @detail Call a given function and print to stdout whether or not it was
 * 		successful.
 * @param test_function	The function to be called.
 */
void runTest(function<bool(void)> test_function)
{
	cout << "========================================\n";
	bool test_passed = test_function();	// call test function and store output

	cout << "\n";
	if (test_passed)
	{
		cout << "Test passed!\n";
	}
	else
	{
		cout << "!!! Test was not successful! !!!\n";
	}
	cout << "========================================" << endl;
}

/**
 * @brief Solve a linear equation.
 * @detail Solves the following equation:
 * 				6 = 2x
 *
 * 			... using basic algebra.
 *
 * 			The answer is `x = 3`.
 *
 * 			Tests the following functions:
 * 			<ul>
 * 			<li>	constructor
 * 			<li>	`divide`
 * 			<li>	`operator==`
 * 			<li>	`operator()`
 * 			</ul>
 */
bool solveEquationOne()
{
	cout << "TEST01: Solve a single linear equation.\n";

	// right-hand side
	Matrix a{1, 1};		// coefficient matrix
	a(1, 1) = 2;
	cout << "\t\tMatrix A:\n" << a << "\n";

	// left-hand side
	Matrix b{1, 1};		// "other-side" matrix
	b(1, 1) = 6;
	cout << "\t\tMatrix B:\n" << b << "\n";

	Matrix x_ans{1, 1};
	x_ans(1, 1) = 3;
	cout << "\t\tAnswer:\n" << x_ans << "\n";

	return b.divide(a) == x_ans;
}

/**
 * @brief Solve a linear equation.
 * @detail Solves the following equation:
 * 					7 = 2x + 1
 *
 * 			... using basic algebra.
 *
 * 			The answer is `x = 3`.
 *
 * 			Tests the following functions:
 * 			<ul>
 * 			<li>	constructor
 *			<li>	`operator-`
 *			<li>	`operator/`
 *			<li>	`operator=`
 *			<li>	`operator==`
 * 			<li>	`operator()`
 * 			</ul>
 */
bool solveEquationTwo()
{
	cout << "TEST02: Solve a linear equation with more arithmetic.\n";

	// right-hand side
	Matrix a{1, 1};		// coefficient matrix
	a(1, 1) = 2;
	cout << "\t\tMatrix A:\n" << a << "\n";

	Matrix c{1, 1};		// constants matrix
	c(1, 1) = 1;
	cout << "\t\tMatrix c:\n" << c << "\n";

	// left-hand side
	Matrix b{1, 1};		// "other-side" matrix
	b(1, 1) = 7;
	cout << "\t\tMatrix B:\n" << b << "\n";

	// correct answer
	Matrix answer{1, 1};
	answer(1, 1) = 3;
	cout << "\t\tAnswer:\n" << answer << "\n";

	// Attempt to solve the equation.
	b = b - c;
	return b.divide(a) == answer;
}

/**
 * @brief Solve a simple system of linear equations.
 * @detail Solves the following system of equations:
 *					7	= 4x1 + 9x2
 *					3	= 5x1 + 2x2
 *
 *			...by converting the system into a matrix equality of the form:
 *					Ax 	= B
 *
 *			...and multiplying by the inverse matrix to produce the
 *			following equation:
 *					x	= (A^-1)B
 *
 *			The answer is:
 *					x1 = 13/37	= 0.351...	(repeating)
 *					x2 = 23/37	= 0.621...	(repeating)
 *
 * 			Tests the following functions:
 * 			<ul>
 * 			<li>	constructor
 * 			<li>	`inverse()`
 * 			<li>	`operator*`
 * 			<li>	`operator()`
 * 			</ul>
 */
bool solveEquationThree()
{
	cout << "TEST03: Solve a system of equations.\n";

	// right-hand side
	Matrix a{2, 2};		// coefficient matrix
	a(1, 1) = 4;
	a(1, 2) = 9;
	a(2, 1) = 5;
	a(2, 2) = 2;
	cout << "\t\tMatrix A:\n" << a << "\n";

	// left-hand side
	Matrix b{2, 1};		// "other-side" matrix
	b(1, 1) = 7;
	b(2, 1) = 3;
	cout << "\t\tMatrix B:\n" << b << "\n";

	// correct answer
	Matrix x_ans{2, 1};
	x_ans(1, 1) = 13.0 / 37;
	x_ans(2, 1) = 23.0 / 37;
	cout << "\t\tAnswer:\n" << x_ans << "\n";

	// Attempt to solve the equation.
	return isApproxEqual(b * a.inverse(), x_ans);
}

/**
 * @brief Solve a system of linear equations in a roundabout way.
 * @detail Solves the following system of equations:
 *					7	= 4x1 + 9x2
 *					3	= 5x1 + 2x2
 *
 *			...by converting the system into a matrix equality of the form:
 *					Ax 	= B
 *
 *			...and multiplying by the inverse matrix to produce the
 *			following equation:
 *					x	= (A^-1)B
 *
 *			The answer is:
 *					x1 = 13/37	= 0.351...	(repeating)
 *					x2 = 23/37	= 0.621...	(repeating)
 *
 *			The following complications are added:
 *			<ul>
 *			<li>	All matrices start as `1x1` matrices and are resized
 *					before use.
 *			<li>	Matrices are populated using a contrived combination
 *					of `operator=` assignments and copy constructions.
 *			<li>	All column vectors start as row vectors and are converted
 *					to column vectors by performing a transpose.
 *			</ul>
 *
 * 			Tests the following functions:
 * 			<ul>
 * 			<li>	constructor
 * 			<li>	copy constructor
 * 			<li>	`inverse()`
 * 			<li>	`operator*`
 * 			<li>	`operator()`
 * 			<li>	`resize()`
 * 			<li>	`transpose()`
 * 			</ul>
 */
bool solveEquationFour()
{
	cout << "TEST04: Solve a system of equations in a contrived way.\n";

	// right-hand side
	Matrix a{1, 1};		// coefficient matrix
	a.resize(2, 2);

	Matrix a_vals{2, 2};// separate matrix containing desired values
	a_vals(1, 1) = 4;
	a_vals(1, 2) = 9;
	a_vals(2, 1) = 5;
	a_vals(2, 2) = 2;

	a = Matrix{a_vals};	// copy construct a_vals and then assign
	cout << "\t\tMatrix A:\n" << a << "\n";

	// If the copy-constructor did what it was supposed to, this shouldn't
	// affect `a` in any way.
	const auto& val_size = a_vals.size();
	for (size_t row = 0; row != val_size.first; ++row)
	{
		for (size_t col = 0; col != val_size.second; ++col)
		{
			a_vals(row, col) = 9001;
		}
	}

	// left-hand side
	Matrix b{1, 2};		// "other-side" matrix, as a row vector
	b(1, 1) = 7;
	b(1, 2) = 3;

	b = b.transpose();	// flip it into a column vector
	cout << "\t\tMatrix B:\n" << b << "\n";

	// correct answer
	Matrix x_ans{2, 1};
	x_ans(1, 1) = 13.0 / 37;
	x_ans(2, 1) = 23.0 / 37;
	cout << "\t\tAnswer:\n" << x_ans << "\n";

	// Attempt to solve the equation.
	return isApproxEqual(b * a.inverse(), x_ans);
}
