#pragma once

#include "Geometry.hpp"

class Drone;

class IGame {
public:
    virtual ~IGame() = default;

    virtual Drone& getMyDrone() = 0;

    virtual int getRemainingBoost() const = 0;
    virtual std::string useBoost() = 0;

    virtual std::size_t getCheckpointCount() const = 0;
    virtual Position getCheckpoint(std::size_t i) const = 0;
};
