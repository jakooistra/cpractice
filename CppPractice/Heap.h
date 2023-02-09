//
//  Heap.h
//  CppPractice
//
//  Created by John Kooistra on 2023-02-08.
//

#ifndef Heap_h
#define Heap_h

#include <stdbool.h>

/* The functions below are exported */
#pragma GCC visibility push(default)

typedef struct HeapImplementation *HeapHandle;

// Creates a min-heap handle.
HeapHandle heapCreate(int size);
HeapHandle heapCreateV(int *values, int count, int size);
void heapRelease(HeapHandle heap);

// Returns false if the value cannot be pushed.
bool heapPush(HeapHandle heap, int value);

// Returns the top value on the heap, or INT_MIN if no value is available.
int heapPeek(HeapHandle heap);

// Removes and returns the top value on the heap, or INT_MIN if no value is available.
int heapPop(HeapHandle heap);

// Returns the number of elements on the heap.
int heapCount(HeapHandle heap);

// Returns true if there are no elements in the heap.
bool heapEmpty(HeapHandle heap);

#pragma GCC visibility pop
#endif /* Heap_h */
