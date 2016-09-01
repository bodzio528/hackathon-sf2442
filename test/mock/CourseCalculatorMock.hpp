#pragma once

#include "../../include/ICourseCalculator.hpp"

#include "gmock/gmock.h"

struct CourseCalculatorMock : ICourseCalculator {
    MOCK_METHOD0(calculateCorrection, Position());
};
