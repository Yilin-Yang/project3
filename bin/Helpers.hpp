#ifndef MAAV_PROJECT_3_HELPERS_HPP
#define MAAV_PROJECT_3_HELPERS_HPP

#include "src/Matrix.hpp"

/**
 * @addtogroup HELPERS Helper Functions
 * @brief Useful functions to be used in the main driver.
 * @{
 */

/**
 * @brief Test two doubles for approximate equality.
 * @return True if values are equal to within a margin of `+/- threshold`,
 * 		false otherwise.
 */
inline bool isApproxEqual(double lhs, double rhs, double threshold)
{
	return lhs < rhs + threshold and lhs > rhs - threshold;
}

/**
 * @brief Test two matrices for approximate equality.
 * @return True if all corresponding Matrix elements are equal to within
 * 		`+/- threshold`, false otherwise. Also return false is matrices have
 * 		different dimensions.
 * @param lhs 		The first Matrix to be compared.
 * @param rhs 		The Matrix against which the first Matrix will be compared.
 * @param threshold A difference of more than this value is considered unequal.
 */
inline bool isApproxEqual(const Matrix& lhs,
						  const Matrix& rhs,
						  double threshold = 0.00001)
{
	const auto& lhs_size = lhs.size();
	if (lhs_size != rhs.size()) return false;

	bool are_equal{true};

	// Loop through and compare all elements of both matrices.
	for (size_t row = 0; row != lhs_size.first; ++row)
	{
		for (size_t col = 0; col != lhs_size.second; ++col)
		{
			// If the elements are too different...
			if (not isApproxEqual(lhs(row, col), rhs(row, col), threshold))
			{
				are_equal = false;

				// Once we know that *one* element is different, we *know*
				// that the matrices are unequal, so we exit *both* for-loops.
				//
				// NOTE:	A "break" statement would only exit the `col` loop;
				// 			it wouldn't break out of both.

				goto loop_exit;	// commit coding heresy
			}
		}
	}
loop_exit:
	// LEARN:	Why the heresy?
	// ANSWER:	`goto` statements are traditionally considered bad style
	// 			(read: heresy) since it's easy to use them in a way that makes
	// 			your code really ugly and confusing ("spaghetti code").
	//
	// 			I think that's generally true, but they're fine if you use
	// 			them sparingly in situations where it makes sense (like
	// 			jumping out of nested loops.)
	//
	// 			Linux Torvalds, the guy that Linux was named after, agrees:
	//				https://goo.gl/2y2XQt

	return are_equal;
}

/**
 * @}
 */

#endif
