#pragma once

#include "Geometry.hpp"

class Drone;

class ITargetCalculator
{
public:
    virtual ~ITargetCalculator() = default;

    virtual Position calculateTarget(Drone const&) = 0;
};
