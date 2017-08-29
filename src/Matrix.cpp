#include "Matrix.hpp"
#include <cassert>		// assert
#include <exception>	// std::runtime_error

using std::ostream;
using std::runtime_error;

using SizePair = std::pair<size_t, size_t>;

Matrix::Matrix(size_t num_rows, size_t num_cols)
{
	// ADD IMPLEMENTATION HERE
}

Matrix::Matrix(const Matrix& to_copy)
{
	// ADD IMPLEMENTATION HERE
}

Matrix& Matrix::operator=(const Matrix& assign_from)
{
	// ADD IMPLEMENTATION HERE
}

Matrix::~Matrix()
{
	// ADD IMPLEMENTATION HERE
}

const SizePair& Matrix::size() const
{
	// ADD IMPLEMENTATION HERE
}

double& Matrix::operator()(size_t row, size_t col)
{
	// ADD IMPLEMENTATION HERE
}

double Matrix::operator()(size_t row, size_t col) const
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

Matrix Matrix::operator/(double divisor) const
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

ostream& operator<<(ostream& os, const Matrix& mat)
{
	// ADD IMPLEMENTATION HERE
}
