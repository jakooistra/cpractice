//
//  TriangleSortedC.c
//  CppPractice
//
//  Created by John Kooistra on 2023-02-08.
//

#include <limits.h>
#include "TriangleSortedC.h"

int getLargestIntTriangleSorted(int const *values, int length) {
    // Degenerate cases - the list is empty/invalid or has exactly one value.
    if (length <= 0) {
        return INT_MIN;
    } else if (length == 1) {
        return values[0];
    }
    
    // All-decreasing or all-increasing cases - the largest value is at the end or beginning.
    if (values[0] > values[1]) {
        return values[0];
    } else if (values[length - 1] > values[length - 2]) {
        return values[length - 1];
    }
    
    // Remaining cases only have possible solutions in the middle of the list.
    int left = 1;
    int right = length - 2;
    
    // Binary search for the answer by testing the midpoint for ascending/descending.
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (values[mid] > values[mid + 1]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    // If the loop exits, left should == right, and the value is at that index.
    return values[left];
}
