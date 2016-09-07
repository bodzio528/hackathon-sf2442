#include "BoostCalculator.hpp"

#include <gtest/gtest.h>

#include "mock/GameMock.hpp"
#include "mock/LapCalculatorMock.hpp"
#include "mock/LongestSegmentCalculatorMock.hpp"

using namespace ::testing;

constexpr int LAP_COUNT = 3;
constexpr int BOOST_COUNT = 4;

struct BoostCalculatorTestData
{
    int laps;
    int boosts;
    int segment;
    int lap;
    int checkpoint;
    int boost;
};

struct BoostCalculatorTestSuite : TestWithParam<BoostCalculatorTestData>
{
    Drone drone;

    StrictMock<GameMock> gameMock;
    StrictMock<LapCalculatorMock> lapMock;
    StrictMock<LongestSegmentCalculatorMock> segmentMock;

    std::unique_ptr<BoostCalculator> sut;

    void SetUp() override;
};

void BoostCalculatorTestSuite::SetUp()
{
    EXPECT_CALL(gameMock, laps()).WillOnce(Return(GetParam().laps));
    EXPECT_CALL(gameMock, boosts()).WillOnce(Return(GetParam().boosts));
    EXPECT_CALL(gameMock, drone()).WillOnce(ReturnRef(drone));

    EXPECT_CALL(segmentMock, longestSegment())
            .WillOnce(Return(GetParam().segment));

    sut = std::make_unique<BoostCalculator>(gameMock, lapMock, segmentMock);
}

TEST_P(BoostCalculatorTestSuite, OnCertainLapCheckpoint_ReturnAvailableBoosts)
{
    drone.nextCheckpoint = GetParam().checkpoint;

    EXPECT_CALL(lapMock, lap()).WillRepeatedly(Return(GetParam().lap));

    EXPECT_THAT(sut->calculateBoost(), Eq(GetParam().boost));
}

// clang-format off
INSTANTIATE_TEST_CASE_P(OneLapOneBoost_Finish, BoostCalculatorTestSuite, Values(
                            // laps, boosts, segment, lap, chkpt, boost?
        BoostCalculatorTestData{1, 1, 2, 1, 0, 1}
));

INSTANTIATE_TEST_CASE_P(OneLapTwoBoosts, BoostCalculatorTestSuite, Values(
        BoostCalculatorTestData{1, 2, 2, 1, 2, 1},
        BoostCalculatorTestData{1, 2, 2, 1, 0, 1}
));

INSTANTIATE_TEST_CASE_P(OneLapThreeBoosts, BoostCalculatorTestSuite, Values(
        BoostCalculatorTestData{1, 3, 2, 1, 2, 1},
        BoostCalculatorTestData{1, 3, 2, 1, 0, 2}
));

INSTANTIATE_TEST_CASE_P(TwoLapsOneBoost_Finish, BoostCalculatorTestSuite, Values(
        BoostCalculatorTestData{2, 1, 2, 2, 0, 1}
));

INSTANTIATE_TEST_CASE_P(TwoLapsTwoBoosts, BoostCalculatorTestSuite, Values(
        BoostCalculatorTestData{2, 2, 2, 2, 2, 1},
        BoostCalculatorTestData{2, 2, 2, 2, 0, 1}
));

INSTANTIATE_TEST_CASE_P(ThreeLapsFourBoosts, BoostCalculatorTestSuite, Values(
        BoostCalculatorTestData{3, 4, 2, 1, 2, 1},
        BoostCalculatorTestData{3, 4, 2, 2, 2, 1},
        BoostCalculatorTestData{3, 4, 2, 3, 2, 1},
        BoostCalculatorTestData{3, 4, 2, 3, 0, 1}
));
