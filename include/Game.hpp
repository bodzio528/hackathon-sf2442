#pragma once

#ifndef AAA
#include <vector>
#include <istream>
#endif

#include "IGame.hpp"

#include "Drone.hpp"
#include "Geometry.hpp"

class Game : public IGame {
public:
    void initialize(std::istream& in) ;
    void update(std::istream& in);

    Drone& getMyDrone() override ;
    int getRemainingBoost() const override ;
    std::string useBoost() override ;
    std::size_t getCheckpointCount() const override ;
    Position getCheckpoint(std::size_t i) const override ;

    int laps;
    int boosts;
    std::vector<Position> checkpoints;
    std::vector<Drone> drones;
};
