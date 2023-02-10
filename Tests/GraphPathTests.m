//
//  GraphPathTests.m
//  Tests
//
//  Created by John Kooistra on 2023-02-10.
//

#import <XCTest/XCTest.h>

#include "GraphPath.h"
#include "Graphs.h"
#include "TestUtilsC.h"

@interface GraphPathTests : XCTestCase

@end

@implementation GraphPathTests

- (void)testDirectedTreeLeftPath {
    GraphHandle graph = createDirectedBinaryTree(15);
    NSArray<NSNumber *> *expected = @[@0, @1, @3, @7];
    IntArrayHandle output = graphPath(graph, 0, 7);
    XCTAssertEqualObjects(expected, nsArray(output));
    arrayRelease(output);
    graphRelease(graph);
}

- (void)testDirectedTreeRightPath {
    GraphHandle graph = createDirectedBinaryTree(15);
    NSArray<NSNumber *> *expected = @[@0, @2, @6, @14];
    IntArrayHandle output = graphPath(graph, 0, 14);
    XCTAssertEqualObjects(expected, nsArray(output));
    arrayRelease(output);
    graphRelease(graph);
}

- (void)testDirectedTreeInvalidLeftReversePath {
    GraphHandle graph = createDirectedBinaryTree(15);
    NSArray<NSNumber *> *expected = @[@7];
    IntArrayHandle output = graphPath(graph, 7, 0);
    XCTAssertEqualObjects(expected, nsArray(output));
    arrayRelease(output);
    graphRelease(graph);
}

- (void)testDirectedTreeInvalidDisconnected {
    GraphHandle graph = createDirectedBinaryTree(15);
    NSArray<NSNumber *> *expected = @[@1];
    IntArrayHandle output = graphPath(graph, 1, 2);
    XCTAssertEqualObjects(expected, nsArray(output));
    arrayRelease(output);
    graphRelease(graph);
}

@end
