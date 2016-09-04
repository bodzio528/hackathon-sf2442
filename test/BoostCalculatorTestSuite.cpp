#include "BoostCalculator.hpp"

#include <gtest/gtest.h>

#include "mock/GameMock.hpp"
#include "mock/LapCalculatorMock.hpp"

using namespace ::testing;

struct BoostCalculatorTestSuite : Test {
    StrictMock<GameMock> gameMock;
    StrictMock<LapCalculatorMock> lapMock;

    std::unique_ptr<BoostCalculator> sut;

    void SetUp() override {
        EXPECT_CALL(gameMock, laps()).WillOnce(Return(0));
        EXPECT_CALL(gameMock, boosts()).WillOnce(Return(0));

        sut = std::make_unique<BoostCalculator>(gameMock, lapMock);
    }
};

TEST_F(BoostCalculatorTestSuite, feil) {
    EXPECT_CALL(lapMock, lap()).WillOnce(Return(0));

    EXPECT_FALSE(sut->calculateBoost());
}
