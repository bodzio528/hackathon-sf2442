#include "Game.hpp"

void Game::initialize(std::istream& in) {
    int playerCount;
    int checkpointCount;
    in >> playerCount >> laps >> boosts >> checkpointCount;

    checkpoints.resize(checkpointCount);
    for (auto& checkpoint : checkpoints) {
        double x, y;
        in >> x >> y;
        checkpoint = { x, y };
    }

    drones.resize(playerCount);
}

void Game::update(std::istream& in) {
    for (auto& drone : drones) {
        double x, y, vx, vy;
        int nextCheckPoint;
        in >> x >> y >> vx >> vy >> nextCheckPoint;
        drone = Drone{ { x, y }, { vx, vy }, nextCheckPoint };
    }
}

Drone& Game::getMyDrone() {
    return drones[0];
}

int Game::getRemainingBoost() const {
    return boosts;
}

std::string Game::useBoost() {
    if (getRemainingBoost()) {
        --boosts;
        return "BOOST";
    }
    return "100";
}

std::size_t Game::getCheckpointCount() const {
    return checkpoints.size();
}

Position Game::getCheckpoint(std::size_t i) const {
    return checkpoints[i];
}
