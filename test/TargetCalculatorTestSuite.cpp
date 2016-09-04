#include "TargetCalculator.hpp"

#include "Drone.hpp"

#include <gtest/gtest.h>

#include "mock/GameMock.hpp"
#include "mock/GeometryMatchers.hpp"

using namespace ::testing;

struct TestRow {
    Position drone;
    Position checkpoint_0;
    Position checkpoint_1;
    Position target;
};

struct TargetCalculatorTestSuite : TestWithParam<TestRow> {
    void SetUp() override {
        sut = std::make_unique<TargetCalculator>(gameMock);
    }

    StrictMock<GameMock> gameMock;

    std::unique_ptr<TargetCalculator> sut;
};

TEST_P(TargetCalculatorTestSuite, feil) {
    Drone drone;
    drone.position = GetParam().drone;

    EXPECT_CALL(gameMock, checkpoints()).WillOnce(Return(2));
    EXPECT_CALL(gameMock, checkpoint(0)).WillOnce(Return(GetParam().checkpoint_0));
    EXPECT_CALL(gameMock, checkpoint(1)).WillOnce(Return(GetParam().checkpoint_1));

    ASSERT_THAT(sut->calculateTarget(drone), VectorEq(GetParam().target));
}

INSTANTIATE_TEST_CASE_P(Instance, TargetCalculatorTestSuite, Values(
    TestRow{ { 1000, 1000}, {    0,     0}, { 1000, -1000}, { 600,      0} },
    TestRow{ {-1000, 1000}, {    0,     0}, { 1000,  1000}, { 0,      600} },
    TestRow{ { 3600, 7200}, { 9600,  7200}, { 6000,  4200}, { 9036,  6996} },
    TestRow{ {-6000,    0}, {    0,     0}, {-3600, -3000}, {-564,  - 204} }
));
