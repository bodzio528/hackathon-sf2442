#include "Game.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;


bool operator==(Drone const& lhs, Drone const& rhs) {
    return lhs.position == rhs.position and lhs.speed == rhs.speed and lhs.nextCheckpoint == rhs.nextCheckpoint;
}

struct GameTestSuite : Test {
    Game sut;
};

TEST_F(GameTestSuite, constructorParsesInitDataString) {
    const std::vector<Position> checkpoints = { { 10, 20 }, { 30, 40 }, { 50, 60 }};

    std::stringstream ss("2   10   3   3  10 20  30 40  50 60");

    sut.initialize(ss);

    EXPECT_THAT(sut.laps, Eq(10));
    EXPECT_THAT(sut.boosts, Eq(3));
    EXPECT_THAT(sut.drones, SizeIs(2));
    EXPECT_THAT(sut.drones, Each(Drone{}));
    EXPECT_THAT(sut.checkpoints, ContainerEq(checkpoints));
}

TEST_F(GameTestSuite, updateParse_SingleDrone) {
    sut.drones.resize(1);

    std::stringstream ss("50 30  5 3  1");

    sut.update(ss);

    EXPECT_THAT(sut.drones[0].position, Eq(Position{50, 30}));
    EXPECT_THAT(sut.drones[0].speed, Eq(Speed{5, 3}));
    EXPECT_THAT(sut.drones[0].nextCheckpoint, Eq(1));
}

TEST_F(GameTestSuite, updateParse_MultipleDrones) {
    sut.drones.resize(3);

    std::stringstream ss("50 30  5 3  1   51 32  6 4  2   54 31  4 7  3");

    sut.update(ss);

    EXPECT_THAT(sut.drones[0], Eq(Drone{{50, 30}, {5, 3}, 1}));
    EXPECT_THAT(sut.drones[1], Eq(Drone{{51, 32}, {6, 4}, 2}));
    EXPECT_THAT(sut.drones[2], Eq(Drone{{54, 31}, {4, 7}, 3}));
}