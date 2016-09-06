#include "TargetCalculator.hpp"

#include "Drone.hpp"
#include "Game.hpp"

#ifndef SF2442_CUMULATIVE
#include <iostream>
#endif

TargetCalculator::TargetCalculator(IGame& game, double radius)
    : m_game(game), m_radius(radius)
{
}

Position TargetCalculator::calculateTarget(Drone const& drone)
{
    auto checkpoint_0 = m_game.checkpoint(drone.nextCheckpoint);
    auto checkpoint_1 = m_game.checkpoint(
            (drone.nextCheckpoint + 1) % m_game.checkpoints());

    auto normalize = [](Vector a) { return a / std::abs(a); };

    auto OA = normalize(drone.position - checkpoint_0);
    auto OB = normalize(checkpoint_1 - checkpoint_0);

    auto OT = m_radius * normalize(OA + OB);

    auto scalar_product = [](Vector a, Vector b) -> double { return a.real()*b.real() + a.imag()*b.imag(); };

    auto course = drone.position - checkpoint_0;
    if (std::abs(scalar_product(drone.speed, drone.position - checkpoint_0 - OT)/std::norm(course) * course) > std::abs(course))
    {
        std::cerr << "checkpoint is near" << std::endl;
    }

    return checkpoint_0 + OT;
}
