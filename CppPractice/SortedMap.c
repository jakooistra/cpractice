//
//  SortedMap.c
//  CppPractice
//
//  Created by John Kooistra on 2023-02-13.
//

#include <stdlib.h>

#include "SortedMap.h"

struct SortedMapNode {
    struct SortedMapEntry entry;
    bool red;
    struct SortedMapNode *left;
    struct SortedMapNode *right;
};

struct SortedMapImplementation {
    int count;
    struct SortedMapNode *root;
};

SortedMapHandle sortedMapCreate(void) {
    SortedMapHandle map = malloc(sizeof(struct SortedMapImplementation));
    map->count = 0;
    map->root = NULL;
    return map;
}

SortedMapHandle sortedMapCreateV(int *keys, int count) {
    SortedMapHandle map = sortedMapCreate();
    for (int i = 0; i < count; ++i) {
        sortedMapInsert(map, keys[i], NULL);
    }
    return map;
}

void sortedMapReleaseNodeRecursively(struct SortedMapNode *node) {
    if (node == NULL) {
        return;
    }
    sortedMapReleaseNodeRecursively(node->left);
    sortedMapReleaseNodeRecursively(node->right);
    free(node);
}

void sortedMapRelease(SortedMapHandle map) {
    sortedMapReleaseNodeRecursively(map->root);
    free(map);
}

//     A            C
//    / \          / \
//   B   C   ->   A   E
//      / \      / \
//     D   E    B   D
void rotateLeft(struct SortedMapNode **node) {
    struct SortedMapNode *root = *node;
    *node = root->right;
    root->right = root->right->left;
    (*node)->left = root;
}

//       A            B
//      / \          / \
//     B   E   ->   C   A
//    / \              / \
//   C   D            D   E
void rotateRight(struct SortedMapNode **node) {
    struct SortedMapNode *root = *node;
    *node = root->left;
    root->left = root->left->right;
    (*node)->right = root;
}

bool isRed(struct SortedMapNode *node) {
    return node == NULL ? false : node->red;
}

void setRed(struct SortedMapNode *node, bool red) {
    if (node != NULL) {
        node->red = red;
    }
}

bool sortedMapInsertAt(struct SortedMapNode **grandparent, struct SortedMapNode **parent, struct SortedMapNode *newNode) {
    bool inserted = false;
    if (newNode->entry.key == (*parent)->entry.key) {
        (*parent)->entry = newNode->entry;
        free(newNode);
        return false;
    } else if (newNode->entry.key < (*parent)->entry.key) {
        if ((*parent)->left == NULL) {
            (*parent)->left = newNode;
            inserted = true;
        } else {
            inserted = sortedMapInsertAt(parent, &(*parent)->left, newNode);
        }
    } else {
        if ((*parent)->right == NULL) {
            (*parent)->right = newNode;
            inserted = true;
        } else {
            inserted = sortedMapInsertAt(parent, &(*parent)->right, newNode);
        }
    }
    
    // Rebalance the tree if an insertion has taken place and altered the tree.
    if (inserted) {
        // If a red-red adjacency has occurred, start rotating.
        if ((*parent)->red && (isRed((*parent)->left) || isRed((*parent)->right))) {
            if (grandparent == NULL) {
                // If there is no grandparent, just recolor the parent. It is the root node.
                (*parent)->red = false;
            } else if (isRed((*grandparent)->left) && isRed((*grandparent)->right)) {
                // If both the parent and uncle nodes are red, recolor them and the grandparent node and recurse back.
                (*grandparent)->red = true;
                setRed((*grandparent)->left, false);
                setRed((*grandparent)->right, false);
            } else if (isRed((*grandparent)->left)) {
                rotateRight(grandparent);
                setRed((*grandparent)->right, true);
                setRed(*grandparent, false);
            } else { // isRed((*grandparent)->right)
                rotateLeft(grandparent);
                setRed((*grandparent)->left, true);
                setRed(*grandparent, false);
            }
        }
    }
    return inserted;
}

bool sortedMapInsert(SortedMapHandle map, int key, void *value) {
    struct SortedMapNode *newNode = malloc(sizeof(struct SortedMapNode));
    newNode->red = true;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->entry.key = key;
    newNode->entry.value = value;
    
    if (map->root == NULL) {
        map->root = newNode;
        map->count++;
        return true;
    } else {
        bool inserted = sortedMapInsertAt(NULL, &map->root, newNode);
        if (inserted) {
            map->count++;
        }
        return inserted;
    }
}

struct SortedMapNode *sortedMapGetNode(struct SortedMapNode *node, int key) {
    while (node != NULL && node->entry.key != key) {
        node = (key < node->entry.key) ? node->left : node->right;
    }
    return node;
}

bool sortedMapErase(SortedMapHandle map, int key) {
    if (map->root == NULL) {
        return false;
    }
    
    // Find the address of the node with the key in its entry.
    struct SortedMapNode **node = &map->root;
    while (*node != NULL && (*node)->entry.key != key) {
        if (key < (*node)->entry.key) {
            node = &(*node)->left;
        } else {
            node = &(*node)->right;
        }
    }
    // The node was not found, return false.
    if (node == NULL) {
        return false;
    }
    
    // TODO: balance with proper red-black rules.
    // Delete a node by shuffling up values one by one.
    while (node != NULL && (*node) != NULL) {
        if ((*node)->left != NULL) {
            (*node)->entry = (*node)->left->entry;
            node = &(*node)->left;
        } else if ((*node)->right != NULL) {
            (*node)->entry = (*node)->right->entry;
            node = &(*node)->right;
        } else {
            free(*node);
            *node = NULL;
            node = NULL;
        }
    }
    map->count--;
    return true;
}

bool sortedMapHasKey(SortedMapHandle map, int key) {
    return sortedMapGetNode(map->root, key) != NULL;
}

void *sortedMapGet(SortedMapHandle map, int key) {
    struct SortedMapNode const *node = sortedMapGetNode(map->root, key);
    return node == NULL ? NULL : node->entry.value;
}

int sortedMapCount(SortedMapHandle map) {
    return map->count;
}

bool sortedMapEmpty(SortedMapHandle map) {
    return map->count == 0;
}

void sortedMapTraverseNode(struct SortedMapNode *node, void *context, void (*visitCallback)(struct SortedMapEntry const *, void *)) {
    if (node == NULL) {
        return;
    }
    sortedMapTraverseNode(node->left, context, visitCallback);
    (*visitCallback)(&node->entry, context);
    sortedMapTraverseNode(node->right, context, visitCallback);
}

void sortedMapTraverse(SortedMapHandle map, void *context, void (*visitCallback)(struct SortedMapEntry const *, void *)) {
    sortedMapTraverseNode(map->root, context, visitCallback);
}

int sortedMapNodeDepth(struct SortedMapNode *node) {
    if (node == NULL) {
        return 0;
    }
    int left = sortedMapNodeDepth(node->left);
    int right = sortedMapNodeDepth(node->right);
    return 1 + ((left > right) ? left : right);
}
        
int sortedMapDebugMaxDepth(SortedMapHandle map) {
    return sortedMapNodeDepth(map->root);
}
