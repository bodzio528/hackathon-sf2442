#include "TargetCalculator.hpp"

#include "Game.hpp"
#include "Drone.hpp"

TargetCalculator::TargetCalculator(IGame &game) : m_game(game) {}

Position TargetCalculator::calculateTarget(Drone const& drone) {
    auto checkpoint_0 = m_game.checkpoint(drone.nextCheckpoint);
    auto checkpoint_1 = m_game.checkpoint((drone.nextCheckpoint + 1) % m_game.checkpoints());

    auto normalize = [](Vector a){ return a / std::abs(a); };

    auto OA = normalize(drone.position - checkpoint_0);
    auto OB = normalize(checkpoint_1   - checkpoint_0);

    auto OT = 600.0 * normalize(OA + OB);

    return checkpoint_0 + OT;
}
