//
//  TriangleSortedTests.mm
//  TriangleSortedTests
//
//  Created by John Kooistra on 2023-02-08.
//

#import <XCTest/XCTest.h>

#import "TestUtils.hpp"
#import "TriangleSorted.hpp"

@interface TriangleSortedTests : XCTestCase

@end

@implementation TriangleSortedTests

- (void)testSimple {
    std::vector<int> input = { 0, 1, 4, 3, 2 };
    NSNumber *expected = @4;
    auto output = numFromOpt(getLargestIntTriangleSorted(input));
    XCTAssertEqualObjects(output, expected);
}

- (void)testEmpty {
    std::vector<int> input = {};
    NSNumber *expected = nil;
    auto output = numFromOpt(getLargestIntTriangleSorted(input));
    XCTAssertEqualObjects(output, expected);
}

- (void)testOne {
    std::vector<int> input = { 10 };
    NSNumber *expected = @10;
    auto output = numFromOpt(getLargestIntTriangleSorted(input));
    XCTAssertEqualObjects(output, expected);
}

- (void)testAllIncreasing {
    std::vector<int> input = { 1, 2, 3, 4, 5 };
    NSNumber *expected = @5;
    auto output = numFromOpt(getLargestIntTriangleSorted(input));
    XCTAssertEqualObjects(output, expected);
}

- (void)testAllDecreasing {
    std::vector<int> input = { 5, 4, 3, 2, 1 };
    NSNumber *expected = @5;
    auto output = numFromOpt(getLargestIntTriangleSorted(input));
    XCTAssertEqualObjects(output, expected);
}

- (void)testEarly {
    std::vector<int> input = { 0, 5, 4, 3, 2, 1 };
    NSNumber *expected = @5;
    auto output = numFromOpt(getLargestIntTriangleSorted(input));
    XCTAssertEqualObjects(output, expected);
}

- (void)testLate {
    std::vector<int> input = { 1, 2, 3, 4, 5, 0 };
    NSNumber *expected = @5;
    auto output = numFromOpt(getLargestIntTriangleSorted(input));
    XCTAssertEqualObjects(output, expected);
}

- (void)testLarge1 {
    std::vector<int> input = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 7, 5, 3, 1 };
    NSNumber *expected = @10;
    auto output = numFromOpt(getLargestIntTriangleSorted(input));
    XCTAssertEqualObjects(output, expected);
}

- (void)testLarge2 {
    std::vector<int> input = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    NSNumber *expected = @20;
    auto output = numFromOpt(getLargestIntTriangleSorted(input));
    XCTAssertEqualObjects(output, expected);
}

@end
