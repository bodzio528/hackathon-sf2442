#pragma once

#include "ICourseCalculator.hpp"

class CourseCalculator : public ICourseCalculator {
public:
    Position calculateCorrection() override;
};
