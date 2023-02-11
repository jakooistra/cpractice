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
    
    // Get a midpoint split value.
    int const midValue = values[count / 2];
    
    int nextHighIndex = count - 1;
    int nextLowIndex = 0;
    while (nextLowIndex < nextHighIndex) {
        while (values[nextLowIndex] < midValue) {
            nextLowIndex++;
        }
        while (nextHighIndex > nextLowIndex && values[nextHighIndex] > midValue) {
            nextHighIndex--;
        }
        
        if (nextLowIndex < nextHighIndex) {
            int swap = values[nextLowIndex];
            values[nextLowIndex] = values[nextHighIndex];
            values[nextHighIndex] = swap;
            while (nextHighIndex > nextLowIndex && values[nextLowIndex] == midValue) {
                nextLowIndex++;
            }
        }
    }
    
    // Recursively sort the array.
    quickSort(values, nextLowIndex);
    quickSort(&values[nextLowIndex], count - nextLowIndex);
}
