//
//  SortedMap.h
//  CppPractice
//
//  Created by John Kooistra on 2023-02-13.
//

#ifndef SortedMap_h
#define SortedMap_h

#include <stdbool.h>

/* The functions below are exported */
#pragma GCC visibility push(default)

typedef struct SortedMapImplementation *SortedMapHandle;

struct SortedMapEntry {
    int key;
    void *value;
};

// Creates a sorted map handle.
SortedMapHandle sortedMapCreate(void);

// Creates a sorted map handle with keys, but null values, generally for testing purposes only.
SortedMapHandle sortedMapCreateV(int *keys, int count);

// Releases all memory associated with the map.
void sortedMapRelease(SortedMapHandle map);

// Returns true if the key is new and unique, and false if the insertion replaced an existing key/value.
bool sortedMapInsert(SortedMapHandle map, int key, void *value);

// Returns true if the key has been removed from the map, false if the value didn't exist.
bool sortedMapErase(SortedMapHandle map, int key);

// Returns true if the map contains the given key.
bool sortedMapHasKey(SortedMapHandle map, int key);

// Returns the associated value for the given key, NULL otherwise.
void *sortedMapGet(SortedMapHandle map, int key);

// Returns the number of elements in the map.
int sortedMapCount(SortedMapHandle map);

// Returns true if there are no elements in the map.
bool sortedMapEmpty(SortedMapHandle map);

// Calls visitCallback in the sorted map order.
void sortedMapTraverse(SortedMapHandle map, void *context, void (*visitCallback)(struct SortedMapEntry const *entry, void *context));

// Returns the maximum depth of all branches in the tree structure of the sorted map.
int sortedMapDebugMaxDepth(SortedMapHandle map);

#pragma GCC visibility pop
#endif /* SortedMap_h */
