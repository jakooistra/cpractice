//
//  GraphPath.c
//  CppPractice
//
//  Created by John Kooistra on 2023-02-10.
//

#include <stdlib.h>
#include <memory.h>

#include "GraphPath.h"

struct NodeVisit {
    int distance;
    int parentNode;
};

IntArrayHandle graphPath(GraphHandle graph, int fromIndex, int toIndex) {
    // Degenerate case, don't bother searching.
    if (toIndex == fromIndex) {
        return arrayCreateVA(1, fromIndex);
    }
    
    struct NodeVisit *visits = malloc(graphNodeCount(graph) * sizeof(struct NodeVisit));
    memset(visits, 0, graphNodeCount(graph) * sizeof(struct NodeVisit));
    
    IntArrayHandle nodesToVisit = arrayCreate(4);
    IntArrayHandle nextNodesToVisit = arrayCreate(4);
    
    arrayPush(nodesToVisit, fromIndex);
    visits[fromIndex].parentNode = -1;
    visits[fromIndex].distance = 1;
    
    int distance = 1;
    while (!arrayEmpty(nodesToVisit)) {
        distance += 1;
        
        // Search the current list of nodes.
        for (int i = 0; i < arrayCount(nodesToVisit); ++i) {
            int toVisit = arrayValue(nodesToVisit, i);
            int edgeCount = graphNodeEdgeCount(graph, toVisit);
            int *edges = graphNodeEdges(graph, toVisit);
            for (int edgeIndex = 0; edgeIndex < edgeCount; ++edgeIndex) {
                int nextNode = edges[edgeIndex];
                // If the node hasn't yet been visited, visit it.
                if (visits[nextNode].distance == 0) {
                    visits[nextNode].distance = distance;
                    visits[nextNode].parentNode = toVisit;
                    arrayPush(nextNodesToVisit, nextNode);
                }
            }
        }
        
        // Search the next list of nodes in the next iteration.
        IntArrayHandle swap = nodesToVisit;
        nodesToVisit = nextNodesToVisit;
        nextNodesToVisit = swap;
        arrayClear(nextNodesToVisit);
        
        if (visits[toIndex].distance > 0) {
            break;
        }
    }
    
    IntArrayHandle path = arrayCreate(visits[toIndex].distance);
    int pathIndex = toIndex;
    while (visits[pathIndex].distance > 1) {
        while (pathIndex != fromIndex) {
            arrayPush(path, pathIndex);
            pathIndex = visits[pathIndex].parentNode;
        }
    }
    arrayPush(path, fromIndex);
    arrayReverse(path);
    
    arrayRelease(nodesToVisit);
    arrayRelease(nextNodesToVisit);
    free(visits);
    
    return path;
}
