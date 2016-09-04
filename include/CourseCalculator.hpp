#pragma once

#include "ICourseCalculator.hpp"

class CourseCalculator : public ICourseCalculator
{
public:
    CourseCalculator(double correction_coefficient);

    Vector calculateCorrection(Drone const& drone, Position target) override;

private:
    double m_correction_coefficient = 3.0;
};
