#include "Logic.hpp"

#include <memory>

#include <gtest/gtest.h>

#include "mock/BoostCalculatorMock.hpp"
#include "mock/CourseCalculatorMock.hpp"
#include "mock/GameMock.hpp"
#include "mock/TargetCalculatorMock.hpp"

#include "Drone.hpp"

using namespace ::testing;

struct LogicTestSuite : Test
{
    StrictMock<GameMock> gameMock;
    StrictMock<CourseCalculatorMock> courseMock;
    StrictMock<TargetCalculatorMock> targetMock;
    NiceMock<BoostCalculatorMock> boostMock;

    std::unique_ptr<Logic> sut;

    void SetUp() override;
};

void LogicTestSuite::SetUp()
{
    sut = std::make_unique<Logic>(gameMock, courseMock, targetMock, boostMock);
}

TEST_F(LogicTestSuite, BoostIsCalculatedByBoostCalculator)
{
    Drone drone;
    Position checkpoint{1000, 1200};

    EXPECT_CALL(gameMock, drone()).WillOnce(ReturnRef(drone));
    EXPECT_CALL(targetMock, calculateTarget(Ref(drone))).WillOnce(Return(checkpoint));
    EXPECT_CALL(courseMock, calculateCorrection(Ref(drone), checkpoint)).WillOnce(Return(c_zero));
    EXPECT_CALL(boostMock, calculateBoost()).WillOnce(Return(true));

    auto cmd = sut->calculateCommand();

    EXPECT_EQ(cmd.thrust, "BOOST");
}

TEST_F(LogicTestSuite, TargetIsCalculatedByTargetCalculator)
{
    Drone drone;
    Position checkpoint{1000, 1200};

    EXPECT_CALL(gameMock, drone()).WillOnce(ReturnRef(drone));
    EXPECT_CALL(targetMock, calculateTarget(Ref(drone))).WillOnce(Return(checkpoint));
    EXPECT_CALL(courseMock, calculateCorrection(Ref(drone), checkpoint)).WillOnce(Return(c_zero));

    auto cmd = sut->calculateCommand();

    EXPECT_EQ(cmd.target, checkpoint);
}

TEST_F(LogicTestSuite, TargetIsCorrectedAdditively)
{
    Drone drone;
    Position checkpoint{1000, 1200};
    Vector correction{100, 200};

    EXPECT_CALL(gameMock, drone()).WillOnce(ReturnRef(drone));
    EXPECT_CALL(targetMock, calculateTarget(Ref(drone))).WillOnce(Return(checkpoint));
    EXPECT_CALL(courseMock, calculateCorrection(Ref(drone), checkpoint)).WillOnce(Return(correction));

    auto cmd = sut->calculateCommand();

    EXPECT_EQ(cmd.target, checkpoint + correction);
}
