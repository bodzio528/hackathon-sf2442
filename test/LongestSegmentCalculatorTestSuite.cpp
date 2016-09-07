#include "LongestSegmentCalculator.hpp"

#include <gtest/gtest.h>

#include "mock/GameMock.hpp"

using namespace ::testing;

struct LongestSegmentCalculatorTestData
{
    std::vector<Position> points;
    int result;
};

struct LongestSegmentCalculatorTestSuite
        : TestWithParam<LongestSegmentCalculatorTestData>
{
    StrictMock<GameMock> gameMock;

    std::unique_ptr<LongestSegmentCalculator> sut;

    void SetUp() override;
};

void LongestSegmentCalculatorTestSuite::SetUp()
{
    sut = std::make_unique<LongestSegmentCalculator>(gameMock);
}

TEST_F(LongestSegmentCalculatorTestSuite, IfNoCheckpoint_ReturnZero)
{
    EXPECT_CALL(gameMock, checkpoints()).WillOnce(Return(0));

    ASSERT_THAT(sut->longestSegment(), Eq(0));
}

TEST_F(LongestSegmentCalculatorTestSuite, IfOneCheckpoint_ReturnZero)
{
    EXPECT_CALL(gameMock, checkpoints()).WillOnce(Return(1));

    ASSERT_THAT(sut->longestSegment(), Eq(0));
}

TEST_F(LongestSegmentCalculatorTestSuite, IfTwoCheckpoints_ReturnZero)
{
    EXPECT_CALL(gameMock, checkpoints()).WillOnce(Return(2));

    ASSERT_THAT(sut->longestSegment(), Eq(0));
}

TEST_P(LongestSegmentCalculatorTestSuite, ReturnEndCheckpointOfLongestSegment)
{
    auto const& checkpoints = GetParam().points;
    EXPECT_CALL(gameMock, checkpoints()).WillOnce(Return(checkpoints.size()));

    for (int i = 0; i < checkpoints.size(); ++i) {
        EXPECT_CALL(gameMock, checkpoint(i)).WillOnce(Return(checkpoints[i]));
    }

    ASSERT_THAT(sut->longestSegment(), Eq(GetParam().result));
}

// clang-format off
INSTANTIATE_TEST_CASE_P(Instance, LongestSegmentCalculatorTestSuite, Values(
        LongestSegmentCalculatorTestData{{ c_origin, c_origin, c_origin }, 2},
        LongestSegmentCalculatorTestData{{ c_origin, {100, 100}, {50, 50} }, 1},
        LongestSegmentCalculatorTestData{{ c_origin, {0, 100}, {100, 0} }, 2},
        LongestSegmentCalculatorTestData{{ c_origin, {100, 100}, {50, 100}, {50, 0} }, 1},
        LongestSegmentCalculatorTestData{{ c_origin, {100, 100}, {200, 0}, {100, -100} }, 3},
        LongestSegmentCalculatorTestData{{ c_origin, {100, 100}, {300, 0}, {100, -100} }, 3}
));
