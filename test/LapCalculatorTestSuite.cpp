#include "LapCalculator.hpp"

#include "Drone.hpp"

#include <gtest/gtest.h>

#include "mock/GameMock.hpp"

using namespace ::testing;

struct LapTestSequence
{
    std::vector<int> checkpoints;
    int currentLeap;
};

struct LapCalculatorTestSuite : TestWithParam<LapTestSequence>
{
    StrictMock<GameMock> gameMock;

    std::unique_ptr<LapCalculator> sut;

    void SetUp() override;
};

void LapCalculatorTestSuite::SetUp()
{
    sut = std::make_unique<LapCalculator>(gameMock);
}

TEST_F(LapCalculatorTestSuite, BeforeUpdateCurrentLeapValueIsZero)
{
    EXPECT_THAT(sut->lap(), Eq(0));
}

TEST_F(LapCalculatorTestSuite, FirstUpdateCausesCurrentLeapValueIsOne)
{
    EXPECT_THAT(sut->lap(), Eq(0));

    Drone drone;
    drone.nextCheckpoint = 1;

    EXPECT_CALL(gameMock, drone()).WillOnce(ReturnRef(drone));

    sut->update();

    EXPECT_THAT(sut->lap(), Eq(1));
}

TEST_P(LapCalculatorTestSuite, CurrentLeapIsNumberOfStartingCheckpointPassesIncludingFirstOne)
{
    for (int checkpoint : GetParam().checkpoints) {
        Drone drone;
        drone.nextCheckpoint = checkpoint;

        EXPECT_CALL(gameMock, drone()).WillOnce(ReturnRef(drone));
        sut->update();
    }

    EXPECT_THAT(sut->lap(), GetParam().currentLeap);
}

// clang-format off
INSTANTIATE_TEST_CASE_P(Instance, LapCalculatorTestSuite, Values(
        LapTestSequence{{1}, 1},
        LapTestSequence{{1, 2}, 1},
        LapTestSequence{{1, 2, 0}, 1},
        LapTestSequence{{1, 2, 0, 1, 1, 2}, 2},
        LapTestSequence{{1, 2, 0, 1}, 2},
        LapTestSequence{{1, 0, 1, 0, 1, 0, 1}, 4}));
