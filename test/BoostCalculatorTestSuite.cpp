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
    bool boost;
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

TEST_P(BoostCalculatorTestSuite, UseBoost_OnCondition_SingleShot)
{
    drone.nextCheckpoint = GetParam().checkpoint;

    EXPECT_CALL(lapMock, lap()).Times(2).WillRepeatedly(Return(GetParam().lap));

    EXPECT_THAT(sut->calculateBoost(), Eq(GetParam().boost));
    EXPECT_THAT(sut->calculateBoost(), Eq(false));
}

// clang-format off
INSTANTIATE_TEST_CASE_P(OneLapOneBoost, BoostCalculatorTestSuite, Values(
                            // laps, boosts, segment, lap, chkpt, boost?
        BoostCalculatorTestData{1, 1, 2, 1, 1, false},
        BoostCalculatorTestData{1, 1, 2, 1, 2, false},
        BoostCalculatorTestData{1, 1, 2, 1, 3, false},
        BoostCalculatorTestData{1, 1, 2, 1, 4, false},
        BoostCalculatorTestData{1, 1, 2, 1, 0, true} //last straight
));

INSTANTIATE_TEST_CASE_P(OneLapTwoBoosts, BoostCalculatorTestSuite, Values(
                            // laps, boosts, segment, lap, chkpt, boost?
        BoostCalculatorTestData{1, 2, 2, 1, 1, false},
        BoostCalculatorTestData{1, 2, 2, 1, 2, true},//longest
        BoostCalculatorTestData{1, 2, 2, 1, 3, false},
        BoostCalculatorTestData{1, 2, 2, 1, 4, false},
        BoostCalculatorTestData{1, 2, 2, 1, 0, true} //last straight
));

INSTANTIATE_TEST_CASE_P(TwoLapsOneBoost, BoostCalculatorTestSuite, Values(
                            // laps, boosts, segment, lap, chkpt, boost?
        BoostCalculatorTestData{2, 1, 2, 1, 1, false},
        BoostCalculatorTestData{2, 1, 2, 1, 2, false},
        BoostCalculatorTestData{2, 1, 2, 1, 3, false},
        BoostCalculatorTestData{2, 1, 2, 1, 0, false},
        BoostCalculatorTestData{2, 1, 2, 2, 1, false},
        BoostCalculatorTestData{2, 1, 2, 2, 2, false},
        BoostCalculatorTestData{2, 1, 2, 2, 3, false},
        BoostCalculatorTestData{2, 1, 2, 2, 0, true} //last straight
));

INSTANTIATE_TEST_CASE_P(TwoLapsTwoBoosts, BoostCalculatorTestSuite, Values(
                            // laps, boosts, segment, lap, chkpt, boost?
        BoostCalculatorTestData{2, 2, 2, 1, 1, false},
        BoostCalculatorTestData{2, 2, 2, 1, 2, false},
        BoostCalculatorTestData{2, 2, 2, 1, 3, false},
        BoostCalculatorTestData{2, 2, 2, 1, 0, false},
        BoostCalculatorTestData{2, 2, 2, 2, 1, false},
        BoostCalculatorTestData{2, 2, 2, 2, 2, true}, // longest
        BoostCalculatorTestData{2, 2, 2, 2, 3, false},
        BoostCalculatorTestData{2, 2, 2, 2, 0, true} //last straight
));

INSTANTIATE_TEST_CASE_P(ThreeLapsFourBoosts, BoostCalculatorTestSuite, Values(
                            // laps, boosts, segment, lap, chkpt, boost?
        BoostCalculatorTestData{3, 4, 2, 1, 1, false},
        BoostCalculatorTestData{3, 4, 2, 1, 2, true},
        BoostCalculatorTestData{3, 4, 2, 1, 3, false},
        BoostCalculatorTestData{3, 4, 2, 1, 0, false},
        BoostCalculatorTestData{3, 4, 2, 2, 1, false},
        BoostCalculatorTestData{3, 4, 2, 2, 2, true},
        BoostCalculatorTestData{3, 4, 2, 2, 3, false},
        BoostCalculatorTestData{3, 4, 2, 2, 0, false},
        BoostCalculatorTestData{3, 4, 2, 3, 1, false} ,
        BoostCalculatorTestData{3, 4, 2, 3, 2, true} ,
        BoostCalculatorTestData{3, 4, 2, 3, 3, false} ,
        BoostCalculatorTestData{3, 4, 2, 3, 0, true} //last straight
));
