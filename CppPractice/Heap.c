//
//  Heap.c
//  CppPractice
//
//  Created by John Kooistra on 2023-02-08.
//


#include <limits.h>
#include <memory.h>
#include <stdlib.h>
#include "Heap.h"

struct HeapImplementation {
    int size;
    int count;
    int *values;
};

HeapHandle heapCreate(int size) {
    struct HeapImplementation *heap = malloc(sizeof(struct HeapImplementation));
    int valuesByteSize = sizeof(int) * size;
    heap->values = malloc(valuesByteSize);
    memset(heap->values, 0, valuesByteSize);
    heap->size = size;
    heap->count = 0;
    return heap;
}

HeapHandle heapCreateV(int *values, int count, int size) {
    HeapHandle heap = heapCreate(size);
    for (int i = 0; i < count; ++i) {
        heapPush(heap, values[i]);
    }
    return heap;
}

void heapRelease(HeapHandle heap) {
    free(heap->values);
    free(heap);
}

static void heapRectifyInsert(HeapHandle heap, int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (heap->values[index] > heap->values[parentIndex]) {
            int swap = heap->values[index];
            heap->values[index] = heap->values[parentIndex];
            heap->values[parentIndex] = swap;
            index = parentIndex;
        } else {
            break;
        }
    }
}

bool heapPush(HeapHandle heap, int value) {
    if (heap->count >= heap->size) {
        return false;
    }
    
    int index = heap->count++;
    heap->values[index] = value;
    heapRectifyInsert(heap, index);
    
    return true;
}

int heapPeek(HeapHandle heap) {
    if (heap->count <= 0) {
        return INT_MIN;
    }
    
    return heap->values[0];
}

int heapPop(HeapHandle heap) {
    if (heap->count <= 0) {
        return INT_MIN;
    }
    
    int value = heap->values[0];
    int emptyIndex = 0;
    while (emptyIndex < heap->count) {
        int leftChild = emptyIndex * 2 + 1;
        int rightChild = leftChild + 1;
        
        if (rightChild < heap->count) {
            // Choose which child to shuffle down the heap and iterate from there.
            if (heap->values[leftChild] > heap->values[rightChild]) {
                heap->values[emptyIndex] = heap->values[leftChild];
                emptyIndex = leftChild;
            } else {
                heap->values[emptyIndex] = heap->values[rightChild];
                emptyIndex = rightChild;
            }
        } else {
            // Iteration is over, at most we have one more shuffle step and then we need to rectify.
            if (leftChild < heap->count) {
                heap->values[emptyIndex] = heap->values[leftChild];
                emptyIndex = leftChild;
            }
            break;
        }
    }
    
    // If the empty index is not the last one, rectify the heap by moving the
    // last value into the empty index and treating it like a normal insert/push.
    if (emptyIndex < heap->count - 1) {
        heap->values[emptyIndex] = heap->values[heap->count - 1];
        heapRectifyInsert(heap, emptyIndex);
    }
    
    heap->count--;
    
    return value;
}

int heapCount(HeapHandle heap) {
    return heap->count;
}

bool heapEmpty(HeapHandle heap) {
    return heap->count == 0;
}
