#pragma once

#include "Geometry.hpp"

class ICourseCalculator {
public:
    virtual ~ICourseCalculator() = default;

    virtual Position calculateCorrection() = 0;
};
