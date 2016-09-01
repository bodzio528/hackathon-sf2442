#include "CourseCalculator.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"

using namespace ::testing;

TEST(CourseCalculatorTestSuite, feil) {
    CourseCalculator calc;
    EXPECT_THAT(13, Eq(12));
}
