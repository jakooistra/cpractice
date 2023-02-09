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

struct GraphNode {
    int edgeCount;
    int *edges;
};

struct GraphImplementation {
    int nodeCount;
    struct GraphNode *nodes;
    int edgePoolSize;
    int edgePoolCount;
    int *edgePool;
};

GraphHandle graphCreate(int nodeCount, int maxEdges) {
    GraphHandle graph = malloc(sizeof(struct GraphImplementation));
    graph->nodeCount = nodeCount;
    
    int nodeByteCount = nodeCount * sizeof(struct GraphNode);
    graph->nodes = malloc(nodeByteCount);
    memset(graph->nodes, 0, nodeByteCount);
    
    graph->edgePoolSize = maxEdges;
    graph->edgePoolCount = 0;
    graph->edgePool = malloc(maxEdges * sizeof(int));
    
    return graph;
}

void graphRelease(GraphHandle graph) {
    free(graph->nodes);
    free(graph->edgePool);
    free(graph);
}

void graphSetNode(GraphHandle graph, int index, int edgeCount, ...) {
    assert(index < graph->nodeCount);
    assert(index >= 0);
    
    struct GraphNode *node = &graph->nodes[index];
    assert(node->edges == NULL);
    
    // Allocate the edges from the graph's pool.
    assert(graph->edgePoolCount + edgeCount <= graph->edgePoolSize);
    node->edges = &graph->edgePool[graph->edgePoolCount];
    node->edgeCount = edgeCount;
    graph->edgePoolCount += edgeCount;
    
    // Set the values of all directed edge connections.
    va_list edges;
    va_start(edges, edgeCount);
    for (int i = 0; i < edgeCount; i++) {
        node->edges[i] = va_arg(edges, int);
    }
    va_end(edges);
}

int graphNodeEdgeCount(GraphHandle graph, int nodeIndex) {
    return graph->nodes[nodeIndex].edgeCount;
}

int *graphNodeEdges(GraphHandle graph, int nodeIndex) {
    return graph->nodes[nodeIndex].edges;
}

int graphNodeCount(GraphHandle graph) {
    return graph->nodeCount;
}


