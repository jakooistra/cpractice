//
//  TriangleSorted.hpp
//  TriangleSorted
//
//  Created by John Kooistra on 2023-02-08.
//

#ifndef TriangleSorted_
#define TriangleSorted_

#include <optional>
#include <vector>

/* The functions below are exported */
#pragma GCC visibility push(default)

/*
 * Returns the largest integer in the given array of values.
 * Assumes that the values are triangle-sorted in increasing-then-decreasing order.
 *
 * Returns std::nullopt if the length passed in is <= 0.
 */
std::optional<int> getLargestIntTriangleSorted(std::vector<int> const &values);

#pragma GCC visibility pop
#endif // TriangleSorted_
