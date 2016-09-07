#include "CourseCalculator.hpp"

#include "Drone.hpp"

#include <gtest/gtest.h>

#include "mock/GeometryMatchers.hpp"

using namespace ::testing;

namespace {
const double CORRECTION_EFFICIENCY = 3.0;
const Vector NO_CORRECTION = {0, 0};
}

struct CourseCalculatorTestSuite : Test
{
    Drone drone;
    Position target;

    std::unique_ptr<CourseCalculator> sut;

    void SetUp() override;
};
void CourseCalculatorTestSuite::SetUp()
{
    sut = std::make_unique<CourseCalculator>(CORRECTION_EFFICIENCY);

    drone.position = {0, 0};
    target = {1000, 1000};
}

TEST_F(CourseCalculatorTestSuite, NoSpeed_NoCorrection)
{
    drone.speed = {0, 0};
    EXPECT_THAT(
            sut->calculateCorrection(drone, target), VectorEq(NO_CORRECTION));
}

TEST_F(CourseCalculatorTestSuite, SpeedIsParallelToCourse_NoCorrection)
{
    drone.speed = {50, 50};
    ASSERT_THAT(drone.speed, VectorParallel(target));
    EXPECT_THAT(
            sut->calculateCorrection(drone, target), VectorEq(NO_CORRECTION));
}

TEST_F(CourseCalculatorTestSuite,
        SpeedIsParallelToCourse_ButOppositeDirection_NoCorrection)
{
    drone.speed = {-50, -50};
    ASSERT_THAT(drone.speed, VectorParallel(target));
    EXPECT_THAT(
            sut->calculateCorrection(drone, target), VectorEq(NO_CORRECTION));
}

TEST_F(CourseCalculatorTestSuite,
        SpeedIsPerpendicularToCourse_PerpendicularSpeedCorrection)
{
    drone.speed = {50, -50};
    ASSERT_THAT(drone.speed, VectorPerpendicular(target));
    EXPECT_THAT(sut->calculateCorrection(drone, target),
            VectorEq(-CORRECTION_EFFICIENCY * drone.speed));
}
