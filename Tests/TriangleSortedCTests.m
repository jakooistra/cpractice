//
//  TriangleSortedCTests.m
//  Tests
//
//  Created by John Kooistra on 2023-02-08.
//

#import <XCTest/XCTest.h>

#import "TestUtilsC.h"
#import "TriangleSortedC.h"

@interface TriangleSortedCTests : XCTestCase

@end

@implementation TriangleSortedCTests

- (void)testSimple {
    const int length = 5;
    int input[length] = { 0, 1, 4, 3, 2 };
    NSNumber *expected = @4;
    NSNumber *output = @(getLargestIntTriangleSorted(input, length));
    XCTAssertEqualObjects(output, expected);
}

- (void)testEmpty {
    const int length = 0;
    int input[length] = {};
    NSNumber *expected = @(INT_MIN);
    NSNumber *output = @(getLargestIntTriangleSorted(input, length));
    XCTAssertEqualObjects(output, expected);
}

- (void)testOne {
    const int length = 1;
    int input[length] = { 10 };
    NSNumber *expected = @10;
    NSNumber *output = @(getLargestIntTriangleSorted(input, length));
    XCTAssertEqualObjects(output, expected);
}

- (void)testAllIncreasing {
    const int length = 5;
    int input[length] = { 1, 2, 3, 4, 5 };
    NSNumber *expected = @5;
    NSNumber *output = @(getLargestIntTriangleSorted(input, length));
    XCTAssertEqualObjects(output, expected);
}

- (void)testAllDecreasing {
    const int length = 5;
    int input[length] = { 5, 4, 3, 2, 1 };
    NSNumber *expected = @5;
    NSNumber *output = @(getLargestIntTriangleSorted(input, length));
    XCTAssertEqualObjects(output, expected);
}

- (void)testEarly {
    const int length = 6;
    int input[length] = { 0, 5, 4, 3, 2, 1 };
    NSNumber *expected = @5;
    NSNumber *output = @(getLargestIntTriangleSorted(input, length));
    XCTAssertEqualObjects(output, expected);
}

- (void)testLate {
    const int length = 6;
    int input[length] = { 1, 2, 3, 4, 5, 0 };
    NSNumber *expected = @5;
    NSNumber *output = @(getLargestIntTriangleSorted(input, length));
    XCTAssertEqualObjects(output, expected);
}

- (void)testLarge1 {
    const int length = 14;
    int input[length] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 7, 5, 3, 1 };
    NSNumber *expected = @10;
    NSNumber *output = @(getLargestIntTriangleSorted(input, length));
    XCTAssertEqualObjects(output, expected);
}

- (void)testLarge2 {
    const int length = 29;
    int input[length] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    NSNumber *expected = @20;
    NSNumber *output = @(getLargestIntTriangleSorted(input, length));
    XCTAssertEqualObjects(output, expected);
}

@end
