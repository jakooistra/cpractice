//
//  QuickSort.c
//  CppPractice
//
//  Created by John Kooistra on 2023-02-11.
//

#include "QuickSort.h"

void quickSort(int *values, int count) {
    if (count <= 2) {
        if (count == 2 && values[0] > values[1]) {
            int swap = values[0];
            values[0] = values[1];
            values[1] = swap;
        }
        return;
    }
    
    // Get a pivot value.
    int const pivotValue = values[0];
    
    // Consider every value in the array and swap and move the pivot when
    int pivot = 0;
    for (int i = 1; i < count; ++i) {
        int value = values[i];
        if (value < pivotValue) {
            values[i] = values[pivot];
            values[pivot++] = value;
        }
    }
    // If the pivot is the first or last index, ensure we don't consider that element.
    pivot = (pivot >= count) ? count - 1 : ((pivot <= 0) ? 1 : pivot);
    
    // Recursively sort the array.
    quickSort(values, pivot);
    quickSort(&values[pivot], count - pivot);
}
