//
//  TriangleSortedC.h
//  CppPractice
//
//  Created by John Kooistra on 2023-02-08.
//

#ifndef TriangleSortedC_h
#define TriangleSortedC_h

/* The functions below are exported */
#pragma GCC visibility push(default)

/*
 * Returns the largest integer in the given array of values.
 * Assumes that the values are triangle-sorted in increasing-then-decreasing order.
 *
 * Returns INT_MIN if the length passed in is <= 0.
 */
int getLargestIntTriangleSorted(int const *values, int length);

#pragma GCC visibility pop

#endif /* TriangleSortedC_h */
