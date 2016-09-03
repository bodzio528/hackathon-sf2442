#pragma once

#include "ITargetCalculator.hpp"

#include <gmock/gmock.h>

struct TargetCalculatorMock : ITargetCalculator {
    MOCK_METHOD1(calculateTarget, Position(Drone const&));
};
