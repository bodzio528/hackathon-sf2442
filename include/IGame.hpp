#pragma once

#include "Geometry.hpp"

class Drone;

class IGame
{
public:
    virtual ~IGame() = default;

    virtual Drone const& drone() const = 0;
    virtual Drone const& drone(int i) const = 0;
    virtual int drones() const = 0;
    virtual int laps() const = 0;
    virtual int boosts() const = 0;
    virtual int checkpoints() const = 0;
    virtual Position checkpoint(int i) const = 0;
};
