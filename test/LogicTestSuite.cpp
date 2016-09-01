#include "Logic.hpp"

#include <memory>

#include "gtest/gtest.h"

#include "mock/GameMock.hpp"
#include "mock/CourseCalculatorMock.hpp"

#include "Drone.hpp"

using namespace ::testing;

struct LogicTestSuite : Test {
    GameMock gameMock;
    CourseCalculatorMock calculatorMock;

    Logic *sut;

    void SetUp() override {
        sut = new Logic(gameMock, calculatorMock);
    }

    void TearDown() override {
        delete sut;
    }
};

TEST_F(LogicTestSuite, callCalculateCommand) {
    Drone drone;

    EXPECT_CALL(gameMock, getMyDrone()).WillOnce(ReturnRef(drone));
    EXPECT_CALL(gameMock, getCheckpoint(0)).WillOnce(Return(Position{1000, 1200}));
//    EXPECT_CALL(gameMock, getCheckpointCount()).WillOnce(Return(2));
//    EXPECT_CALL(gameMock, getCheckpoint(1)).WillOnce(Return(Position{1800, 2000}));

    auto cmd = sut->calculateCommand();
}