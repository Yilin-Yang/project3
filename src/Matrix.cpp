#include "Matrix.hpp"
#include <cassert>		// assert
#include <exception>	// std::runtime_error

using std::ostream;
using std::runtime_error;

Matrix::Matrix(size_t num_rows, size_t num_cols)
{
	// ADD IMPLEMENTATION HERE
}

Matrix& resize(size_t num_rows, size_t num_cols)
{
	// ADD IMPLEMENTATION HERE
}

Matrix Matrix::operator+(const Matrix& rhs) const
{
	// ADD IMPLEMENTATION HERE
}

Matrix Matrix::operator-(const Matrix& rhs) const
{
	// ADD IMPLEMENTATION HERE
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
	// ADD IMPLEMENTATION HERE
}

Matrix Matrix::divide(const Matrix& rhs) const
{
	// ADD IMPLEMENTATION HERE
}

Matrix Matrix::inverse() const
{
	// ADD IMPLEMENTATION HERE
}

Matrix Matrix::transpose() const
{
	// ADD IMPLEMENTATION HERE
}

bool Matrix::operator==(const Matrix& rhs) const
{
	// ADD IMPLEMENTATION HERE
}

bool Matrix::operator!=(const Matrix& rhs) const
{
	// ADD IMPLEMENTATION HERE
}

ostream& Matrix::operator<<(ostream& os) const
{
	// ADD IMPLEMENTATION HERE
}
