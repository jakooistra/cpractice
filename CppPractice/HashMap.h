//
//  HashMap.h
//  CppPractice
//
//  Created by John Kooistra on 2023-02-14.
//

#ifndef HashMap_h
#define HashMap_h

#include <stdbool.h>

/* The functions below are exported */
#pragma GCC visibility push(default)

typedef struct HashMapImplementation *HashMapHandle;

struct HashMapEntry {
    int key;
    void *value;
};

// Creates a hash map handle.
HashMapHandle hashMapCreate(void);

// Creates a hash map handle with keys, but null values, generally for testing purposes only.
HashMapHandle hashMapCreateV(int *keys, int count);

// Releases all memory associated with the map.
void hashMapRelease(HashMapHandle map);

// Returns true if the key is new and unique, and false if the insertion replaced an existing key/value.
bool hashMapInsert(HashMapHandle map, int key, void *value);

// Returns true if the key has been removed from the map, false if the value didn't exist.
bool hashMapErase(HashMapHandle map, int key);

// Returns true if the map contains the given key.
bool hashMapHasKey(HashMapHandle map, int key);

// Returns the associated value for the given key, NULL otherwise.
void *hashMapGet(HashMapHandle map, int key);

// Returns the number of elements in the map.
int hashMapCount(HashMapHandle map);

// Returns true if there are no elements in the map.
bool hashMapEmpty(HashMapHandle map);

// Calls visitCallback in an undefined order with all values inside the map.
void hashMapTraverse(HashMapHandle map, void *context, void (*visitCallback)(struct HashMapEntry const *entry, void *context));

// Returns the allocated size of the hash map.
int hashMapAllocatedSize(HashMapHandle map);

#pragma GCC visibility pop
#endif /* HashMap_h */
