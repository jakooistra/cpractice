//
//  QuickSort.h
//  CppPractice
//
//  Created by John Kooistra on 2023-02-11.
//

#ifndef QuickSort_h
#define QuickSort_h

/* The functions below are exported */
#pragma GCC visibility push(default)

// Sorts the values into increasing order in-place in n*log(n) time complexity.
void quickSort(int *values, int count);

#pragma GCC visibility pop
#endif /* QuickSort_h */
