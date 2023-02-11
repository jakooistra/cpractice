//
//  TestUtilsC.h
//  CppPractice
//
//  Created by John Kooistra on 2023-02-08.
//

#ifndef TestUtilsC_h
#define TestUtilsC_h

#include "IntArray.h"

static inline NSMutableArray<NSNumber *> *nsArray(IntArrayHandle array) {
    NSMutableArray<NSNumber *> *output = [NSMutableArray arrayWithCapacity:arrayCount(array)];
    for (int i = 0; i < arrayCount(array); ++i) {
        [output addObject:@(arrayValue(array, i))];
    }
    return output;
}

static inline NSMutableArray<NSNumber *> *nsArrayV(int *values, int count) {
    NSMutableArray<NSNumber *> *output = [NSMutableArray arrayWithCapacity:count];
    for (int i = 0; i < count; ++i) {
        [output addObject:@(values[i])];
    }
    return output;
}

#endif /* TestUtilsC_h */
