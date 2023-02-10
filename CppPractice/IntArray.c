//
//  IntArray.c
//  CppPractice
//
//  Created by John Kooistra on 2023-02-09.
//

#include <stdarg.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

#include "IntArray.h"

struct IntArrayImplementation {
    int count;
    int size;
    int *values;
};

IntArrayHandle arrayCreate(int size) {
    IntArrayHandle array = malloc(sizeof(struct IntArrayImplementation));
    array->count = 0;
    array->size = size < 1 ? 1 : size;
    array->values = malloc(array->size * sizeof(int));
    return array;
}

IntArrayHandle arrayCreateVA(int count, ...) {
    IntArrayHandle array = arrayCreate(count);
    array->count = count;
    
    va_list values;
    va_start(values, count);
    for (int i = 0; i < count; ++i) {
        array->values[i] = va_arg(values, int);
    }
    va_end(values);
    
    return array;
}

void arrayRelease(IntArrayHandle array) {
    free(array->values);
    free(array);
}

void arrayPush(IntArrayHandle array, int value) {
    if (array->count >= array->size) {
        arrayReserveSize(array, array->size * 2);
    }
    
    array->values[array->count++] = value;
}

int arrayPop(IntArrayHandle array) {
    if (array->count <= 0) {
        return INT_MIN;
    }
    return array->values[--array->count];
}

int arrayRemove(IntArrayHandle array, int index) {
    int value = array->values[index];
    for (int i = index + 1; i < array->count; ++i) {
        array->values[i - 1] = array->values[i];
    }
    array->count--;
    return value;
}

bool arrayRemoveFirstValue(IntArrayHandle array, int value) {
    for (int i = 0; i < array->count; ++i) {
        if (array->values[i] == value) {
            arrayRemove(array, i);
            return true;
        }
    }
    return false;
}

void arrayClear(IntArrayHandle array) {
    array->count = 0;
}

int arrayValue(IntArrayHandle array, int index) {
    return array->values[index];
}

int *arrayValues(IntArrayHandle array) {
    return array->values;
}

int arrayCount(IntArrayHandle array) {
    return array->count;
}

bool arrayEmpty(IntArrayHandle array) {
    return array->count == 0;
}

void arrayReserveSize(IntArrayHandle array, int newSize) {
    if (newSize > array->size) {
        array->size = newSize;
        int *newValues = malloc(array->size * sizeof(int));
        memcpy(newValues, array->values, array->count * sizeof(int));
        free(array->values);
        array->values = newValues;
    }
}

int arrayAllocatedSize(IntArrayHandle array) {
    return array->size;
}

void arrayReverse(IntArrayHandle array) {
    for (int i = (array->count - 1) / 2; i >= 0; --i) {
        int swapIndex = array->count - i - 1;
        int swap = array->values[i];
        array->values[i] = array->values[swapIndex];
        array->values[swapIndex] = swap;
    }
}
