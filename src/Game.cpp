#include "Game.hpp"

void Game::initialize(std::istream& in) {
    int playerCount;
    int checkpointCount;
    in >> playerCount >> m_laps >> m_boosts >> checkpointCount;

    m_checkpoints.resize(checkpointCount);
    for (auto& checkpoint : m_checkpoints) {
        double x, y;
        in >> x >> y;
        checkpoint = { x, y };
    }

    m_drones.resize(playerCount);
}

void Game::update(std::istream& in) {
    for (auto& drone : m_drones) {
        double x, y, vx, vy;
        int nextCheckPoint;
        in >> x >> y >> vx >> vy >> nextCheckPoint;
        drone = Drone{ { x, y }, { vx, vy }, nextCheckPoint };
    }
}

Drone const& Game::drone() const {
    return m_drones[0];
}

Drone const& Game::drone(int i) const {
    return m_drones[i];
}

int Game::drones() const {
    return m_drones.size();
}

int  Game::laps() const {

    return m_laps;
}

int Game::boosts() const {
    return m_boosts;
}

int Game::checkpoints() const {
    return m_checkpoints.size();
}

Position Game::checkpoint(int i) const {
    return m_checkpoints.at(i);
}
