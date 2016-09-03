#include "CourseCalculator.hpp"

#include "Drone.hpp"

#include <gtest/gtest.h>

#include "mock/GeometryMatchers.hpp"

using namespace ::testing;

struct CourseCalculatorTestSuite : Test {
    Drone drone;
    Position target;

    void SetUp() override {

        sut = std::make_unique<CourseCalculator>(correction_coefficient);

        drone.position = { 0, 0 };
        target = { 1000, 1000 };
    }

    std::unique_ptr<CourseCalculator> sut;

    const double correction_coefficient = 3.0;
    const Vector no_correction = {0, 0};
};

TEST_F(CourseCalculatorTestSuite, NoSpeed_NoCorrection) {
    drone.speed = { 0, 0 };
    EXPECT_THAT(sut->calculateCorrection(drone, target), VectorEq(no_correction));
}

TEST_F(CourseCalculatorTestSuite, SpeedIsParallelToCourse_NoCorrection) {
    drone.speed = { -50, -50 };
    ASSERT_THAT(drone.speed, VectorParallel(target));
    EXPECT_THAT(sut->calculateCorrection(drone, target), VectorEq(no_correction));
}

TEST_F(CourseCalculatorTestSuite, SpeedIsPerpendicularToCourse_PerpendicularSpeedCorrection) {
    drone.speed = { 50, -50 };
    ASSERT_THAT(drone.speed, VectorPerpendicular(target));
    EXPECT_THAT(sut->calculateCorrection(drone, target), VectorEq(-correction_coefficient*drone.speed));
}
