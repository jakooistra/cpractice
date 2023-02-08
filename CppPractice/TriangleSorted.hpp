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

/* The classes below are exported */
#pragma GCC visibility push(default)

std::optional<int> getLargestIntTriangleSorted(std::vector<int> const &values);

#pragma GCC visibility pop
#endif // TriangleSorted_
