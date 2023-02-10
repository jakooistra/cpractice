//
//  Graph.c
//  CppPractice
//
//  Created by John Kooistra on 2023-02-09.
//

#include <stdarg.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#include "Graph.h"
#include "IntArray.h"

struct GraphImplementation {
    int nodeCount;
    IntArrayHandle *nodes;
};

GraphHandle graphCreate(int nodeCount) {
    GraphHandle graph = malloc(sizeof(struct GraphImplementation));
    graph->nodeCount = nodeCount;
    
    int nodeByteCount = nodeCount * sizeof(IntArrayHandle);
    graph->nodes = malloc(nodeByteCount);
    memset(graph->nodes, 0, nodeByteCount);
    
    return graph;
}

void graphRelease(GraphHandle graph) {
    for (int i = 0; i < graph->nodeCount; ++i) {
        IntArrayHandle array = graph->nodes[i];
        if (array != NULL) {
            arrayRelease(array);
        }
    }
    free(graph->nodes);
    free(graph);
}

void graphAddNodeEdges(GraphHandle graph, int index, int edgeCount, ...) {
    assert(index < graph->nodeCount);
    assert(index >= 0);
    
    IntArrayHandle node = graph->nodes[index];
    if (node == NULL) {
        node = arrayCreate(edgeCount);
        graph->nodes[index] = node;
    } else {
        arrayReserveSize(node, edgeCount + arrayCount(node));
    }
    
    // Set the values of all directed edge connections.
    va_list edges;
    va_start(edges, edgeCount);
    for (int i = 0; i < edgeCount; i++) {
        graphAddNodeEdge(graph, index, va_arg(edges, int));
    }
    va_end(edges);
}

void graphAddNodeEdge(GraphHandle graph, int fromIndex, int toIndex) {
    assert(fromIndex < graph->nodeCount);
    assert(fromIndex >= 0);
    assert(toIndex < graph->nodeCount);
    assert(toIndex >= 0);
    
    IntArrayHandle node = graph->nodes[fromIndex];
    if (node == NULL) {
        node = arrayCreate(4);
        graph->nodes[fromIndex] = node;
    }
    arrayPush(node, toIndex);
}

void graphClearNodeEdges(GraphHandle graph, int index) {
    assert(index < graph->nodeCount);
    assert(index >= 0);
    
    if (graph->nodes[index] != NULL) {
        arrayRelease(graph->nodes[index]);
        graph->nodes[index] = NULL;
    }
}

void graphConnectNodes(GraphHandle graph, int index0, int index1) {
    graphAddNodeEdge(graph, index0, index1);
    graphAddNodeEdge(graph, index1, index0);
}

int graphNodeEdgeCount(GraphHandle graph, int nodeIndex) {
    IntArrayHandle node = graph->nodes[nodeIndex];
    return node == NULL ? 0 : arrayCount(node);
}

int *graphNodeEdges(GraphHandle graph, int nodeIndex) {
    IntArrayHandle node = graph->nodes[nodeIndex];
    return node == NULL ? 0 : arrayValues(node);
}

int graphNodeCount(GraphHandle graph) {
    return graph->nodeCount;
}
