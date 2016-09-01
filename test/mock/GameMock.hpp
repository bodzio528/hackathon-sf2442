#pragma once

#include "../../include/IGame.hpp"

#include "gmock/gmock.h"

struct GameMock : IGame {
    MOCK_METHOD0(getMyDrone, Drone&());
    MOCK_CONST_METHOD0(getRemainingBoost, int());
    MOCK_METHOD0(useBoost, std::string());
    MOCK_CONST_METHOD0(getCheckpointCount, std::size_t());
    MOCK_CONST_METHOD1(getCheckpoint, Position(std::size_t));
};
