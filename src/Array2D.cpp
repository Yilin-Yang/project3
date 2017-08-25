#include "Array2D.hpp"

Array2D::Array2D(size_t num_rows, size_t num_cols)
{
	// ADD IMPLEMENTATION HERE
}

Array2D::Array2D(const Array2D& to_copy)
{
	// ADD IMPLEMENTATION HERE
}


Array2D& Array2D::operator=(const Array2D& assign_from)
{
	// ADD IMPLEMENTATION HERE
}

Array2D::~Array2D()
{
	// ADD IMPLEMENTATION HERE

	// HINT:	Remember, use `delete[]` to delete arrays!
	// 			`delete` only deletes the first object the pointer points to!
}

const SizePair& Array2D::size() const
{
	// ADD IMPLEMENTATION HERE
}


double& Array2D::operator()(size_t row, size_t col)
{
	// ADD IMPLEMENTATION HERE
}


double Array2D::operator()(size_t row, size_t col) const
{
	// ADD IMPLEMENTATION HERE
}


double& Array2D::operator[](size_t index)
{
	// ADD IMPLEMENTATION HERE
}

double Array2D::operator[](size_t index) const
{
	// ADD IMPLEMENTATION HERE
}
