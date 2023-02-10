//
//  GraphTests.m
//  Tests
//
//  Created by John Kooistra on 2023-02-09.
//

#import <XCTest/XCTest.h>

#include "Graph.h"

@interface GraphTests : XCTestCase

@end

static NSArray<NSNumber *> *nsGraphEdges(GraphHandle graph, int nodeIndex) {
    int edgeCount = graphNodeEdgeCount(graph, nodeIndex);
    NSMutableArray<NSNumber *> *output = [NSMutableArray array];
    int *edges = graphNodeEdges(graph, nodeIndex);
    for (int i = 0; i < edgeCount; ++i) {
        [output addObject:@(edges[i])];
    }
    return output;
}

@implementation GraphTests

- (void)testCreation {
    GraphHandle graph = graphCreate(4);
    graphAddNodeEdges(graph, 0, 3, 1, 2, 3);
    graphAddNodeEdges(graph, 1, 3, 0, 2, 3);
    graphAddNodeEdges(graph, 2, 3, 1, 0, 3);
    graphAddNodeEdges(graph, 3, 3, 1, 2, 0);
    XCTAssertEqual(4, graphNodeCount(graph));
    XCTAssertEqual(3, graphNodeEdgeCount(graph, 0));
    XCTAssertEqual(3, graphNodeEdgeCount(graph, 1));
    XCTAssertEqual(3, graphNodeEdgeCount(graph, 2));
    XCTAssertEqual(3, graphNodeEdgeCount(graph, 3));
    graphRelease(graph);
}

- (void)testEdgeIndexRetrieval {
    GraphHandle graph = graphCreate(4);
    graphAddNodeEdges(graph, 0, 3, 1, 2, 3);
    graphAddNodeEdges(graph, 1, 3, 0, 2, 3);
    graphAddNodeEdges(graph, 2, 3, 1, 0, 3);
    graphAddNodeEdges(graph, 3, 3, 1, 2, 0);
    NSArray<NSNumber *> *expected0 = @[@1, @2, @3];
    NSArray<NSNumber *> *expected1 = @[@0, @2, @3];
    NSArray<NSNumber *> *expected2 = @[@1, @0, @3];
    NSArray<NSNumber *> *expected3 = @[@1, @2, @0];
    XCTAssertEqualObjects(expected0, nsGraphEdges(graph, 0));
    XCTAssertEqualObjects(expected1, nsGraphEdges(graph, 1));
    XCTAssertEqualObjects(expected2, nsGraphEdges(graph, 2));
    XCTAssertEqualObjects(expected3, nsGraphEdges(graph, 3));
    graphRelease(graph);
}

@end
