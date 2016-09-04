#pragma once

#include "IGame.hpp"
#include "Drone.hpp"

#include <gmock/gmock.h>

struct GameMock : IGame {
    MOCK_CONST_METHOD0(drone, Drone const&());
    MOCK_CONST_METHOD1(drone, Drone const&(int));
    MOCK_CONST_METHOD0(drones, int());
    MOCK_CONST_METHOD0(laps, int());
    MOCK_CONST_METHOD0(boosts, int());
    MOCK_CONST_METHOD0(checkpoints, int());
    MOCK_CONST_METHOD1(checkpoint, Position(int));
};
