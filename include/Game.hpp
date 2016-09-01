#pragma once

#include <vector>
#include <istream>

#include "IGame.hpp"

#include "Drone.hpp"
#include "Geometry.hpp"

class Game : public IGame {
public:
    int laps;
    int boosts;
    std::vector<Position> checkpoints;
    std::vector<Drone> drones;

    Drone& getMyDrone() override {
        return drones[0];
    }

    int getRemainingBoost() const override {
        return boosts;
    }

    std::string useBoost() override {
        if (getRemainingBoost()) {
            --boosts;
            return "BOOST";
        }
        return "100";
    }

    std::size_t getCheckpointCount() const override {
        return checkpoints.size();
    }

    Position getCheckpoint(std::size_t i) const override {
        return checkpoints[i];
    }

    void initialize(std::istream& in) {
        int playerCount;
        int checkpointCount;
        in >> playerCount >> laps >> boosts >> checkpointCount;

        checkpoints.resize(checkpointCount);
        for (auto& checkpoint : checkpoints) {
            int x, y;
            in >> x >> y;
            checkpoint = { x, y };
        }

        drones.resize(playerCount);
    }

    void update(std::istream& in) {
        for (auto& drone : drones) {
            int x, y, vx, vy, nextCheckPoint;
            in >> x >> y >> vx >> vy >> nextCheckPoint;
            drone = Drone{ { x, y }, { vx, vy }, nextCheckPoint };
        }
    }
};
