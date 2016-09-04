#include "Game.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

MATCHER(DroneEmpty, "")
{
    return arg.position == c_origin and arg.speed == c_static and arg.nextCheckpoint == 0;
}

MATCHER_P(DroneEq, value, "")
{
    return value.position == arg.position and value.speed == arg.speed and value.nextCheckpoint == arg.nextCheckpoint;
}

struct GameTestSuite : Test
{
    void SetUp() override;

    std::unique_ptr<Game> sut;
};

void GameTestSuite::SetUp()
{
    sut = std::make_unique<Game>();
}

TEST_F(GameTestSuite, initializeParsesInitDataString)
{
    std::stringstream ss("2   10   3   3  10 20  30 40  50 60");

    sut->initialize(ss);

    EXPECT_THAT(sut->laps(), Eq(10));
    EXPECT_THAT(sut->boosts(), Eq(3));
    EXPECT_THAT(sut->drones(), Eq(2));
    EXPECT_THAT(sut->drone(0), DroneEmpty());
    EXPECT_THAT(sut->drone(1), DroneEmpty());
    EXPECT_THAT(sut->checkpoints(), Eq(3));
    EXPECT_THAT(sut->checkpoint(0), Eq(Position{10, 20}));
    EXPECT_THAT(sut->checkpoint(1), Eq(Position{30, 40}));
    EXPECT_THAT(sut->checkpoint(2), Eq(Position{50, 60}));
}

struct GameUpdateTestSuite : GameTestSuite
{
    void initializeSingleDrone()
    {
        std::stringstream ss;
        ss << "1 0 0 0";

        sut->initialize(ss);
    }

    void initializeMultipleDrones()
    {
        std::stringstream ss;
        ss << "3 0 0 0";

        sut->initialize(ss);
    }
};

TEST_F(GameUpdateTestSuite, updateParse_SingleDrone)
{
    initializeSingleDrone();

    std::stringstream ss("50 30  5 3  1");

    sut->update(ss);

    EXPECT_THAT(sut->drone(), DroneEq(Drone{{50, 30}, {5, 3}, 1}));
}

TEST_F(GameUpdateTestSuite, updateParse_MultipleDrones)
{
    initializeMultipleDrones();

    std::stringstream ss("50 30  5 3  1   51 32  6 4  2   54 31  4 7  3");

    sut->update(ss);

    EXPECT_THAT(sut->drone(0), DroneEq(Drone{{50, 30}, {5, 3}, 1}));
    EXPECT_THAT(sut->drone(1), DroneEq(Drone{{51, 32}, {6, 4}, 2}));
    EXPECT_THAT(sut->drone(2), DroneEq(Drone{{54, 31}, {4, 7}, 3}));
}
