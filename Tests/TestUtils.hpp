//
//  TestUtils.hpp
//  CppPractice
//
//  Created by John Kooistra on 2023-02-08.
//

#ifndef TestUtils_h
#define TestUtils_h

#include <optional>

static NSNumber *numFromOpt(std::optional<int> const &value) {
    if (value.has_value()) {
        return @(value.value());
    } else {
        return nil;
    }
}

#endif /* TestUtils_h */
