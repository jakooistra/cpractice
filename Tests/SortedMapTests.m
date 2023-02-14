//
//  SortedMapTests.m
//  Tests
//
//  Created by John Kooistra on 2023-02-13.
//

#import <XCTest/XCTest.h>

#include "SortedMap.h"
#include "TestUtilsC.h"
#include "IntArray.h"

@interface SortedMapTests : XCTestCase
@end

static void extractMapNodeKey(struct SortedMapEntry const *entry, void *context) {
    IntArrayHandle array = context;
    arrayPush(array, entry->key);
}

static NSArray<NSNumber *> *allKeys(SortedMapHandle map) {
    IntArrayHandle array = arrayCreate(sortedMapCount(map));
    sortedMapTraverse(map, array, &extractMapNodeKey);
    NSArray<NSNumber *> *output = nsArray(array);
    arrayRelease(array);
    return output;
}

@implementation SortedMapTests

- (void)testSortedInputOrder {
    int keys[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    NSArray<NSNumber *> *expected = @[@1, @2, @3, @4, @5, @6, @7, @8, @9, @10];
    SortedMapHandle map = sortedMapCreateV(keys, 10);
    XCTAssertEqualObjects(expected, allKeys(map));
    XCTAssertEqual(10, sortedMapCount(map));
    sortedMapRelease(map);
}

- (void)testUnsortedInputOrder {
    int keys[10] = { 5, 2, 3, 8, 9, 6, 1, 10, 4, 7 };
    NSArray<NSNumber *> *expected = @[@1, @2, @3, @4, @5, @6, @7, @8, @9, @10];
    SortedMapHandle map = sortedMapCreateV(keys, 10);
    XCTAssertEqualObjects(expected, allKeys(map));
    XCTAssertEqual(10, sortedMapCount(map));
    sortedMapRelease(map);
}

- (void)testMapInsertBalancing {
    SortedMapHandle map = sortedMapCreate();
    for (int i = 0; i < 1000; ++i) {
        sortedMapInsert(map, i, NULL);
    }
    XCTAssertLessThanOrEqual(sortedMapDebugMaxDepth(map), 20);
    XCTAssertEqual(1000, sortedMapCount(map));
    sortedMapRelease(map);
}

- (void)testMapEraseBalancing {
    SortedMapHandle map = sortedMapCreate();
    for (int i = 0; i < 20000; ++i) {
        sortedMapInsert(map, i, NULL);
    }
    for (int i = 0; i < 19000; ++i) {
        sortedMapErase(map, i);
    }
    XCTAssertLessThanOrEqual(sortedMapDebugMaxDepth(map), 20);
    XCTAssertEqual(1000, sortedMapCount(map));
    sortedMapRelease(map);
}

- (void)testMapKeyRetrieval {
    SortedMapHandle map = sortedMapCreate();
    for (int i = 0; i < 1000; ++i) {
        sortedMapInsert(map, i, NULL);
    }
    for (int i = 0; i < 1000; ++i) {
        XCTAssertTrue(sortedMapHasKey(map, i));
    }
    XCTAssertFalse(sortedMapHasKey(map, -1));
    XCTAssertFalse(sortedMapHasKey(map, 1000));
    XCTAssertEqual(1000, sortedMapCount(map));
    sortedMapRelease(map);
}

- (void)testMapEmpty {
    SortedMapHandle map = sortedMapCreate();
    XCTAssertTrue(sortedMapEmpty(map));
    for (int i = 0; i < 1000; ++i) {
        XCTAssertTrue(sortedMapInsert(map, i, NULL));
    }
    XCTAssertFalse(sortedMapEmpty(map));
    for (int i = 0; i < 1000; ++i) {
        XCTAssertTrue(sortedMapErase(map, i));
    }
    XCTAssertTrue(sortedMapEmpty(map));
    sortedMapRelease(map);
}

- (void)testMapValueRetrieval {
    SortedMapHandle map = sortedMapCreate();
    for (int i = 0; i < 1000; ++i) {
        void *value = (void*)(long)(i + 100);
        sortedMapInsert(map, i, value);
    }
    XCTAssertEqual((void*)250l, sortedMapGet(map, 150));
    sortedMapRelease(map);
}

@end
