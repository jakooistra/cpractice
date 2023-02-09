//
//  HeapTests.m
//  Tests
//
//  Created by John Kooistra on 2023-02-08.
//

#import <XCTest/XCTest.h>

#include "Heap.h"

@interface HeapTests : XCTestCase

@end

static NSArray<NSNumber *> *drainHeap(HeapHandle heap) {
    NSMutableArray<NSNumber *> *values = [NSMutableArray array];
    while (!heapEmpty(heap)) {
        [values addObject:@(heapPop(heap))];
    }
    return values;
}

@implementation HeapTests

- (void)testMinOrder {
    int values[3] = {1, 2, 3};
    HeapHandle heap = heapCreateV(values, 3, 32);
    NSArray<NSNumber *> *expected = @[@3, @2, @1];
    XCTAssertEqualObjects(expected, drainHeap(heap));
    heapRelease(heap);
}

- (void)testMaxOrder {
    int values[3] = {3, 2, 1};
    HeapHandle heap = heapCreateV(values, 3, 32);
    NSArray<NSNumber *> *expected = @[@3, @2, @1];
    XCTAssertEqualObjects(expected, drainHeap(heap));
    heapRelease(heap);
}

- (void)test132 {
    int values[3] = {1, 3, 2};
    HeapHandle heap = heapCreateV(values, 3, 32);
    NSArray<NSNumber *> *expected = @[@3, @2, @1];
    XCTAssertEqualObjects(expected, drainHeap(heap));
    heapRelease(heap);
}

- (void)test213 {
    int values[3] = {2, 1, 3};
    HeapHandle heap = heapCreateV(values, 3, 32);
    NSArray<NSNumber *> *expected = @[@3, @2, @1];
    XCTAssertEqualObjects(expected, drainHeap(heap));
    heapRelease(heap);
}

- (void)test231 {
    int values[3] = {2, 3, 1};
    HeapHandle heap = heapCreateV(values, 3, 32);
    NSArray<NSNumber *> *expected = @[@3, @2, @1];
    XCTAssertEqualObjects(expected, drainHeap(heap));
    heapRelease(heap);
}

- (void)test312 {
    int values[3] = {3, 1, 2};
    HeapHandle heap = heapCreateV(values, 3, 32);
    NSArray<NSNumber *> *expected = @[@3, @2, @1];
    XCTAssertEqualObjects(expected, drainHeap(heap));
    heapRelease(heap);
}

- (void)testLarge {
    int values[32] = {
        1, 2, 4, 5, 7, 8, 10, 11, 9, 6, 3, 12, 16, 15, 14, 13,
        16, 14, 12, 11, 13, 7, 5, 6, 4, 8, 3, 2, 9, 10, 15, 1
    };
    HeapHandle heap = heapCreateV(values, 32, 32);
    NSArray<NSNumber *> *expected = @[
        @16, @16, @15, @15, @14, @14, @13, @13, @12, @12, @11, @11, @10, @10,
        @9, @9, @8, @8, @7, @7, @6, @6, @5, @5, @4, @4, @3, @3, @2, @2, @1, @1
    ];
    XCTAssertEqual(32, heapCount(heap));
    XCTAssertEqualObjects(expected, drainHeap(heap));
    XCTAssertEqual(0, heapCount(heap));
    heapRelease(heap);
}

- (void)testInsertLimit {
    int values[7] = {1, 2, 3, 4, 5, 6, 7};
    HeapHandle heap = heapCreateV(values, 7, 4);
    NSArray<NSNumber *> *expected = @[@4, @3, @2, @1];
    XCTAssertEqual(4, heapCount(heap));
    XCTAssertEqualObjects(expected, drainHeap(heap));
    heapRelease(heap);
}

- (void)testPeek {
    int values[8] = {1, 2, 10, 4, 5, 6, 7, 9};
    HeapHandle heap = heapCreateV(values, 8, 8);
    NSNumber *expected = @10;
    XCTAssertEqualObjects(expected, @(heapPeek(heap)));
    XCTAssertEqual(8, heapCount(heap));
    heapRelease(heap);
}

- (void)testEmptyPeek {
    HeapHandle heap = heapCreate(8);
    NSNumber *expected = @(INT_MIN);
    XCTAssertEqualObjects(expected, @(heapPeek(heap)));
    XCTAssertEqual(0, heapCount(heap));
    heapRelease(heap);
}

- (void)testEmptyPop {
    int values[8] = {1, 2, 10, 4, 5, 6, 7, 9};
    HeapHandle heap = heapCreateV(values, 8, 8);
    drainHeap(heap);
    NSNumber *expected = @(INT_MIN);
    XCTAssertEqualObjects(expected, @(heapPop(heap)));
    XCTAssertEqual(0, heapCount(heap));
    heapRelease(heap);
}

@end
