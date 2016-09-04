#pragma once

#include "Geometry.hpp"

class Drone;

class ICourseCalculator
{
public:
    virtual ~ICourseCalculator() = default;

    virtual Vector calculateCorrection(Drone const& drone, Position target) = 0;
};
