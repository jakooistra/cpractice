//
//  QuickSortTests.m
//  Tests
//
//  Created by John Kooistra on 2023-02-11.
//

#import <XCTest/XCTest.h>

#include "QuickSort.h"
#include "TestUtilsC.h"

@interface QuickSortTests : XCTestCase
@end

@implementation QuickSortTests

- (void)test012 {
    int array[3] = {0, 1, 2};
    NSArray<NSNumber *> *expected = [nsArrayV(array, 3) sortedArrayUsingSelector:@selector(compare:)];
    quickSort(array, 3);
    XCTAssertEqualObjects(expected, nsArrayV(array, 3));
}

- (void)test021 {
    int array[3] = {0, 2, 1};
    NSArray<NSNumber *> *expected = [nsArrayV(array, 3) sortedArrayUsingSelector:@selector(compare:)];
    quickSort(array, 3);
    XCTAssertEqualObjects(expected, nsArrayV(array, 3));
}

- (void)test102 {
    int array[3] = {1, 0, 2};
    NSArray<NSNumber *> *expected = [nsArrayV(array, 3) sortedArrayUsingSelector:@selector(compare:)];
    quickSort(array, 3);
    XCTAssertEqualObjects(expected, nsArrayV(array, 3));
}

- (void)test120 {
    int array[3] = {1, 2, 0};
    NSArray<NSNumber *> *expected = [nsArrayV(array, 3) sortedArrayUsingSelector:@selector(compare:)];
    quickSort(array, 3);
    XCTAssertEqualObjects(expected, nsArrayV(array, 3));
}

- (void)test210 {
    int array[3] = {2, 1, 0};
    NSArray<NSNumber *> *expected = [nsArrayV(array, 3) sortedArrayUsingSelector:@selector(compare:)];
    quickSort(array, 3);
    XCTAssertEqualObjects(expected, nsArrayV(array, 3));
}

- (void)test201 {
    int array[3] = {2, 0, 1};
    NSArray<NSNumber *> *expected = [nsArrayV(array, 3) sortedArrayUsingSelector:@selector(compare:)];
    quickSort(array, 3);
    XCTAssertEqualObjects(expected, nsArrayV(array, 3));
}

- (void)testLarge {
    int array[21] = {2, 0, 1, 20, 19, 14, 15, 16, 4, 3, 9, 7, 8, 5, 12, 13, 10, 11, 18, 17, 6};
    NSArray<NSNumber *> *expected = [nsArrayV(array, 21) sortedArrayUsingSelector:@selector(compare:)];
    quickSort(array, 21);
    XCTAssertEqualObjects(expected, nsArrayV(array, 21));
}

- (void)testDuplicates {
    int array[20] = {5, 5, 5, 8, 8, 6, 6, 9, 9, 1, 1, 2, 2, 0, 4, 2, 6, 3, 1, 0};
    NSArray<NSNumber *> *expected = [nsArrayV(array, 20) sortedArrayUsingSelector:@selector(compare:)];
    quickSort(array, 20);
    XCTAssertEqualObjects(expected, nsArrayV(array, 20));
}

@end
