//
//  IntArray.h
//  CppPractice
//
//  Created by John Kooistra on 2023-02-09.
//

#ifndef IntArray_h
#define IntArray_h

#include <stdbool.h>

/* The functions below are exported */
#pragma GCC visibility push(default)

typedef struct IntArrayImplementation *IntArrayHandle;

// Creates an auto-sizing array handle.
IntArrayHandle arrayCreate(int size);
IntArrayHandle arrayCreateVA(int count, ...);
void arrayRelease(IntArrayHandle array);

void arrayPush(IntArrayHandle array, int value);

int arrayPop(IntArrayHandle array);
int arrayRemove(IntArrayHandle array, int index);
bool arrayRemoveFirstValue(IntArrayHandle array, int value);
void arrayClear(IntArrayHandle array);

int arrayValue(IntArrayHandle array, int index);
int *arrayValues(IntArrayHandle array);

int arrayCount(IntArrayHandle array);
bool arrayEmpty(IntArrayHandle array);

void arrayReserveSize(IntArrayHandle array, int size);
int arrayAllocatedSize(IntArrayHandle array);

void arrayReverse(IntArrayHandle array);

#pragma GCC visibility pop
#endif /* IntArray_h */
