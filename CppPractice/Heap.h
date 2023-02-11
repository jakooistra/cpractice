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

struct HeapEntry {
    int value;
    void *context;
};

// Creates a min-heap handle.
HeapHandle heapCreate(int size);

// Creates a min-heap handle with values, but null contexts, generally for testing purposes only.
HeapHandle heapCreateV(int *values, int count, int size);

// Releases all memory associated with the heap.
void heapRelease(HeapHandle heap);

// Returns false if the value cannot be pushed.
bool heapPush(HeapHandle heap, int value, void *context);

// Returns the top value on the heap, or INT_MIN if no value is available.
struct HeapEntry heapPeek(HeapHandle heap);

// Removes and returns the top value on the heap, or INT_MIN if no value is available.
struct HeapEntry heapPop(HeapHandle heap);

// Returns the number of elements on the heap.
int heapCount(HeapHandle heap);

// Returns true if there are no elements in the heap.
bool heapEmpty(HeapHandle heap);

#pragma GCC visibility pop
#endif /* Heap_h */
