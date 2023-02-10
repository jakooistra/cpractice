//
//  GraphUtil.h
//  CppPractice
//
//  Created by John Kooistra on 2023-02-10.
//

#ifndef GraphPath_h
#define GraphPath_h

#include <stdbool.h>

#include "Graph.h"
#include "IntArray.h"

/* The functions below are exported */
#pragma GCC visibility push(default)

IntArrayHandle graphPath(GraphHandle graph, int fromIndex, int toIndex);

#pragma GCC visibility pop
#endif /* GraphPath_h */
