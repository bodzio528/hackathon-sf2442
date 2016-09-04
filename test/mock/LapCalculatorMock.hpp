#pragma once

#include "ILapCalculator.hpp"

#include <gmock/gmock.h>

struct LapCalculatorMock : ILapCalculator
{
    MOCK_CONST_METHOD0(lap, int());
};
