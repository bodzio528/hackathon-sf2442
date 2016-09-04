#pragma once

#ifndef SF2442_CUMULATIVE
#include <istream>
#include <vector>
#endif

#include "IGame.hpp"

#include "Drone.hpp"
#include "Geometry.hpp"

class Game : public IGame {
public:
    void initialize(std::istream& in) ;
    void update(std::istream& in);

    Drone const& drone() const override ;
    Drone const& drone(int i) const override ;
    int drones() const override ;
    int laps() const override ;
    int boosts() const override ;
    Position checkpoint(int i) const override ;
    int checkpoints() const override ;

private:
    int m_laps;
    int m_boosts;
    std::vector<Position> m_checkpoints;
    std::vector<Drone> m_drones;
};
