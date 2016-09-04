#include "LapCalculator.hpp"

#include "IGame.hpp"

#include "Drone.hpp"

LapCalculator::LapCalculator(IGame const& game)
    : m_game(game)
{
}

void LapCalculator::update()
{
    Drone const& drone = m_game.drone();

    if (drone.nextCheckpoint != m_nextCheckpoint) {
        if (drone.nextCheckpoint == 1) {
            ++m_leap;
        }

        m_nextCheckpoint = drone.nextCheckpoint;
    }
}

int LapCalculator::lap() const { return m_leap; }
