//
//  Graphs.c
//  Tests
//
//  Created by John Kooistra on 2023-02-10.
//

#include "Graphs.h"

GraphHandle createDirectedBinaryTree(int nodeCount) {
    GraphHandle graph = graphCreate(nodeCount);
    for (int i = 1; i < nodeCount; ++i) {
        graphAddNodeEdge(graph, (i - 1) / 2, i);
    }
    return graph;
}
