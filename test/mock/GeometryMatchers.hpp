#pragma once

#include "Geometry.hpp"

#include <gmock/gmock.h>

using ::testing::DoubleNear;

MATCHER_P(VectorEq, value, "")
{
    constexpr double DIST_TOLERANCE = .5;

    return std::abs(value.real() - arg.real()) < DIST_TOLERANCE and
           std::abs(value.imag() - arg.imag()) < DIST_TOLERANCE;
}

MATCHER_P(VectorParallel, value, "")
{
    constexpr double PARALLEL_TOLERANCE = 0.0625;
    return std::abs(std::sin(std::arg(value) - std::arg(arg))) < PARALLEL_TOLERANCE;
}

MATCHER_P(VectorPerpendicular, value, "")
{
    constexpr double PERPENDICULAR_TOLERANCE = 0.0625;
    return std::abs(std::cos(std::arg(value) - std::arg(arg))) < PERPENDICULAR_TOLERANCE;
}
