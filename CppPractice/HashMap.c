//
//  HashMap.c
//  CppPractice
//
//  Created by John Kooistra on 2023-02-14.
//

#include <stdlib.h>
#include <memory.h>

#include "HashMap.h"

#define DEFAULT_MAP_SIZE    (61)

static int nextSizeUp(int currentSize) {
    return (currentSize * 2) + 5;
}

static int getResizeCount(int size) {
    return (size * 7) / 10;
}

struct HashMapNode {
    struct HashMapEntry entry;
    struct HashMapNode *next;
};

struct HashMapImplementation {
    int count;
    int resizeCount;
    int size;
    struct HashMapNode **array;
    struct HashMapNode *allocatedNodes;
    struct HashMapNode *headAvailableNode;
};

void allocateMapSize(HashMapHandle map, int size) {
    map->size = size;
    map->resizeCount = getResizeCount(map->size);
    map->array = malloc(sizeof(struct HashMapNode *) * map->size);
    memset(map->array, 0, sizeof(struct HashMapNode *) * map->size);
    map->allocatedNodes = malloc(sizeof(struct HashMapNode) * map->size);
    map->headAvailableNode = map->allocatedNodes;
    for (int i = map->size - 1; i > 0; --i) {
        map->allocatedNodes[i-1].next = &map->allocatedNodes[i];
    }
    map->allocatedNodes[map->size - 1].next = NULL;
}

HashMapHandle hashMapCreate(void) {
    HashMapHandle map = malloc(sizeof(struct HashMapImplementation));
    map->count = 0;
    allocateMapSize(map, DEFAULT_MAP_SIZE);
    return map;
}

HashMapHandle hashMapCreateV(int *keys, int count) {
    HashMapHandle map = hashMapCreate();
    for (int i = 0; i < count; ++i) {
        hashMapInsert(map, keys[i], NULL);
    }
    return map;
}

void hashMapRelease(HashMapHandle map) {
    free(map->array);
    free(map->allocatedNodes);
    free(map);
}

int hashIndex(HashMapHandle map, int key) {
    return key % map->size;
}

struct HashMapNode *popNode(HashMapHandle map, int key, void *value) {
    struct HashMapNode *node = map->headAvailableNode;
    node->entry.key = key;
    node->entry.value = value;
    map->headAvailableNode = node->next;
    node->next = NULL;
    return node;
}

void reuseNode(HashMapHandle map, struct HashMapNode *node) {
    node->next = map->headAvailableNode;
    map->headAvailableNode = node;
}

bool hashMapInsert(HashMapHandle map, int key, void *value) {
    if (map->count + 1 >= map->resizeCount) {
        int oldSize = map->size;
        struct HashMapNode **oldArray = map->array;
        struct HashMapNode *oldAllocatedNodes = map->allocatedNodes;
        allocateMapSize(map, nextSizeUp(map->size));
        map->count = 0;
        
        for (int i = 0; i < oldSize; ++i) {
            struct HashMapNode *node = oldArray[i];
            while (node != NULL) {
                hashMapInsert(map, node->entry.key, node->entry.value);
                node = node->next;
            }
        }
        
        free(oldAllocatedNodes);
        free(oldArray);
    }
    
    int index = hashIndex(map, key);
    struct HashMapNode *existingNode = map->array[index];
    
    // Determine if the value already exists, and exit early.
    struct HashMapNode *node = existingNode;
    while (node != NULL) {
        if (node->entry.key == key) {
            return false;
        }
        node = node->next;
    }
    
    // Insert the new key/value pair.
    map->array[index] = popNode(map, key, value);
    map->array[index]->next = existingNode;
    map->count++;
    return true;
}

bool hashMapErase(HashMapHandle map, int key) {
    int index = hashIndex(map, key);
    struct HashMapNode **node = &map->array[index];
    while (*node != NULL) {
        if ((*node)->entry.key == key) {
            struct HashMapNode *removedNode = *node;
            *node = removedNode->next;
            reuseNode(map, removedNode);
            map->count--;
            return true;
        }
        node = &(*node)->next;
    }
    return false;
}

bool hashMapHasKey(HashMapHandle map, int key) {
    int index = hashIndex(map, key);
    struct HashMapNode *node = map->array[index];
    while (node != NULL) {
        if (node->entry.key == key) {
            return true;
        }
        node = node->next;
    }
    return false;
}

void *hashMapGet(HashMapHandle map, int key) {
    int index = hashIndex(map, key);
    struct HashMapNode *node = map->array[index];
    while (node != NULL) {
        if (node->entry.key == key) {
            return node->entry.value;
        }
        node = node->next;
    }
    return NULL;
}

int hashMapCount(HashMapHandle map) {
    return map->count;
}

bool hashMapEmpty(HashMapHandle map) {
    return map->count == 0;
}

void hashMapTraverse(HashMapHandle map, void *context, void (*visitCallback)(struct HashMapEntry const *entry, void *context)) {
    for (int i = 0; i < map->size; ++i) {
        struct HashMapNode *node = map->array[i];
        while (node != NULL) {
            (*visitCallback)(&node->entry, context);
            node = node->next;
        }
    }
}

int hashMapAllocatedSize(HashMapHandle map) {
    return map->size;
}
