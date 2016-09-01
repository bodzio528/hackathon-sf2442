#include "Logic.hpp"

#include <memory>

#include "gtest/gtest.h"

#include "mock/GameMock.hpp"
#include "mock/CourseCalculatorMock.hpp"

#include "Drone.hpp"

using namespace ::testing;

struct LogicTestSuite : Test {
    StrictMock<GameMock> gameMock;
    StrictMock<CourseCalculatorMock> calculatorMock;

    std::unique_ptr<Logic> sut;

    void SetUp() override {
        sut.reset(new Logic(gameMock, calculatorMock));
    }
};

TEST_F(LogicTestSuite, TargetIsCorrectedAdditively) {
    Drone drone;
    Position checkpoint{1000, 1200};
    Vector correction{100, 200};

    EXPECT_CALL(gameMock, getMyDrone()).WillOnce(ReturnRef(drone));
    EXPECT_CALL(gameMock, getCheckpoint(0)).WillOnce(Return(checkpoint));
    EXPECT_CALL(calculatorMock, calculateCorrection(Ref(drone), checkpoint)).WillOnce(Return(correction));

    auto cmd = sut->calculateCommand();

    EXPECT_EQ(cmd.target, checkpoint + correction);
}
