#pragma once

#include "ICourseCalculator.hpp"

class CourseCalculator : public ICourseCalculator {
public:
    Vector calculateCorrection(Drone const& drone, Position target) override;
};
