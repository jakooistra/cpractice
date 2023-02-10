//
//  Graph.h
//  CppPractice
//
//  Created by John Kooistra on 2023-02-09.
//

#ifndef Graph_h
#define Graph_h

/* The functions below are exported */
#pragma GCC visibility push(default)

typedef struct GraphImplementation *GraphHandle;

GraphHandle graphCreate(int nodeCount);
void graphRelease(GraphHandle graph);

// Adds to a node's directed edges.
void graphAddNodeEdges(GraphHandle graph, int index, int edgeCount, ...);
void graphAddNodeEdge(GraphHandle graph, int fromIndex, int toIndex);

// Removes a node's directed edges.
void graphClearNodeEdges(GraphHandle graph, int index);

// Adds directed edges between nodes in both directions.
void graphConnectNodes(GraphHandle graph, int index0, int index1);

// Returns the number of directed edges for a given node index.
int graphNodeEdgeCount(GraphHandle graph, int nodeIndex);

// Returns an array of connected node indices for a given node index.
int *graphNodeEdges(GraphHandle graph, int nodeIndex);

// Returns the number of nodes in the graph.
int graphNodeCount(GraphHandle graph);

#pragma GCC visibility pop
#endif /* Graph_h */
