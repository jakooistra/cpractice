//
//  TriangleSorted.cpp
//  TriangleSorted
//
//  Created by John Kooistra on 2023-02-08.
//

#include "TriangleSorted.hpp"

std::optional<int> getLargestIntTriangleSorted(std::vector<int> const &values) {
    // Degenerate cases - the list is empty or has exactly one value.
    if (values.empty()) {
        return std::nullopt;
    } else if (values.size() == 1) {
        return values[0];
    }
    
    // All-decreasing or all-increasing cases - the largest value is at the end or beginning.
    if (values[0] > values[1]) {
        return values[0];
    } else if (values[values.size() - 1] > values[values.size() - 2]) {
        return *values.rbegin();
    }
    
    // Remaining cases only have possible solutions in the middle of the list.
    size_t left = 1;
    size_t right = values.size() - 2;
    
    // Binary search for the answer by testing the midpoint for ascending/descending.
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (values[mid] > values[mid+1]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    // If the loop exits, left should == right, and the value is at that index.
    return values[left];
}
