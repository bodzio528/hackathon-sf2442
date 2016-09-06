#pragma once

#include "ILongestSegmentCalculator.hpp"

#include <gmock/gmock.h>

struct LongestSegmentCalculatorMock : ILongestSegmentCalculator
{
    MOCK_CONST_METHOD0(longestSegment, int());
};
