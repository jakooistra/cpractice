//
//  HashMapTests.m
//  Tests
//
//  Created by John Kooistra on 2023-02-14.
//

#import <XCTest/XCTest.h>

#include "HashMap.h"
#include "TestUtilsC.h"

@interface HashMapTests : XCTestCase
@end

static void extractMapNodeKey(struct HashMapEntry const *entry, void *context) {
    IntArrayHandle array = context;
    arrayPush(array, entry->key);
}

static NSArray<NSNumber *> *allKeys(HashMapHandle map) {
    IntArrayHandle array = arrayCreate(hashMapCount(map));
    hashMapTraverse(map, array, &extractMapNodeKey);
    NSArray<NSNumber *> *output = nsArray(array);
    arrayRelease(array);
    return output;
}

@implementation HashMapTests

- (void)testUnsortedInputOrder {
    int keys[10] = { 5, 2, 3, 8, 9, 6, 1, 10, 4, 7 };
    NSArray<NSNumber *> *expected = @[@1, @2, @3, @4, @5, @6, @7, @8, @9, @10];
    HashMapHandle map = hashMapCreateV(keys, 10);
    XCTAssertEqualObjects(expected, allKeys(map));
    XCTAssertEqual(10, hashMapCount(map));
    hashMapRelease(map);
}

- (void)testMapInsertResizing {
    HashMapHandle map = hashMapCreate();
    for (int i = 0; i < 1000; ++i) {
        hashMapInsert(map, i, NULL);
    }
    XCTAssertLessThanOrEqual(hashMapAllocatedSize(map), (1000 * 2 * 10 + 6) / 7);
    XCTAssertGreaterThanOrEqual(hashMapAllocatedSize(map), (1000 * 10) / 7);
    XCTAssertEqual(1000, hashMapCount(map));
    hashMapRelease(map);
}

- (void)testMapKeyRetrieval {
    HashMapHandle map = hashMapCreate();
    for (int i = 0; i < 2000; ++i) {
        hashMapInsert(map, i, NULL);
    }
    for (int i = 0; i < 1000; ++i) {
        hashMapErase(map, i);
    }
    for (int i = 1000; i < 2000; ++i) {
        XCTAssertTrue(hashMapHasKey(map, i));
    }
    XCTAssertFalse(hashMapHasKey(map, 999));
    XCTAssertFalse(hashMapHasKey(map, 2000));
    XCTAssertEqual(1000, hashMapCount(map));
    hashMapRelease(map);
}

- (void)testMapEmpty {
    HashMapHandle map = hashMapCreate();
    XCTAssertTrue(hashMapEmpty(map));
    for (int i = 0; i < 1000; ++i) {
        XCTAssertTrue(hashMapInsert(map, i, NULL));
    }
    XCTAssertFalse(hashMapEmpty(map));
    for (int i = 0; i < 1000; ++i) {
        XCTAssertTrue(hashMapErase(map, i));
    }
    XCTAssertTrue(hashMapEmpty(map));
    hashMapRelease(map);
}

- (void)testMapValueRetrieval {
    HashMapHandle map = hashMapCreate();
    for (int i = 0; i < 1000; ++i) {
        void *value = (void*)(long)(i + 100);
        hashMapInsert(map, i, value);
    }
    XCTAssertEqual((void*)250l, hashMapGet(map, 150));
    hashMapRelease(map);
}

@end
