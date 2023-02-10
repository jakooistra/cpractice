//
//  ArrayTests.m
//  Tests
//
//  Created by John Kooistra on 2023-02-09.
//

#import <XCTest/XCTest.h>

#include "IntArray.h"

@interface ArrayTests : XCTestCase

@end

static NSMutableArray<NSNumber *> *nsArray(IntArrayHandle array) {
    NSMutableArray<NSNumber *> *output = [NSMutableArray arrayWithCapacity:arrayCount(array)];
    for (int i = 0; i < arrayCount(array); ++i) {
        [output addObject:@(arrayValue(array, i))];
    }
    return output;
}

@implementation ArrayTests

- (void)testReallocatingPush {
    IntArrayHandle array = arrayCreate(2);
    arrayPush(array, 1);
    arrayPush(array, 2);
    arrayPush(array, 3);
    XCTAssertEqual(4, arrayAllocatedSize(array));
    XCTAssertEqual(3, arrayCount(array));
    NSArray<NSNumber *> *expected = @[@1, @2, @3];
    XCTAssertEqualObjects(expected, nsArray(array));
    arrayRelease(array);
}

- (void)testPop {
    IntArrayHandle array = arrayCreateVA(4, 1, 2, 3, 4);
    int value = arrayPop(array);
    XCTAssertEqual(4, value);
    NSArray<NSNumber *> *expected = @[@1, @2, @3];
    XCTAssertEqualObjects(expected, nsArray(array));
    XCTAssertEqual(4, arrayAllocatedSize(array));
    arrayRelease(array);
}

- (void)testValidRemove {
    IntArrayHandle array = arrayCreateVA(4, 1, 2, 4, 3);
    bool removed = arrayRemoveFirstValue(array, 4);
    XCTAssertTrue(removed);
    NSArray<NSNumber *> *expected = @[@1, @2, @3];
    XCTAssertEqualObjects(expected, nsArray(array));
    XCTAssertEqual(4, arrayAllocatedSize(array));
    arrayRelease(array);
}

- (void)testInvalidRemove {
    IntArrayHandle array = arrayCreateVA(4, 1, 2, 4, 3);
    bool removed = arrayRemoveFirstValue(array, 4321);
    XCTAssertFalse(removed);
    NSArray<NSNumber *> *expected = @[@1, @2, @4, @3];
    XCTAssertEqualObjects(expected, nsArray(array));
    XCTAssertEqual(4, arrayAllocatedSize(array));
    arrayRelease(array);
}

- (void)testPopUntilEmpty {
    IntArrayHandle array = arrayCreateVA(2, 1, 2);
    XCTAssertFalse(arrayEmpty(array));
    XCTAssertEqual(2, arrayPop(array));
    XCTAssertEqual(1, arrayPop(array));
    XCTAssertEqual(INT_MIN, arrayPop(array));
    XCTAssertTrue(arrayEmpty(array));
    arrayRelease(array);
}

- (void)testReservePreservesValues {
    IntArrayHandle array = arrayCreateVA(2, 1, 2);
    NSArray<NSNumber *> *expected = @[@1, @2];
    
    XCTAssertEqual(2, arrayAllocatedSize(array));
    XCTAssertEqualObjects(expected, nsArray(array));
    
    arrayReserveSize(array, 16);
    XCTAssertEqual(16, arrayAllocatedSize(array));
    XCTAssertEqualObjects(expected, nsArray(array));
    
    arrayRelease(array);
}

@end
