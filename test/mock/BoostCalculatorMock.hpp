#pragma once

#include "IBoostCalculator.hpp"

#include <gmock/gmock.h>

struct BoostCalculatorMock : IBoostCalculator
{
    MOCK_METHOD0(calculateBoost, bool());
};
