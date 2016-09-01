#pragma once

#include "ICourseCalculator.hpp"

#include "gmock/gmock.h"

struct CourseCalculatorMock : ICourseCalculator {
    MOCK_METHOD2(calculateCorrection, Position(Drone const&, Position));
};
