#include "BoostCalculator.hpp"

#include "IGame.hpp"
#include "ILapCalculator.hpp"

BoostCalculator::BoostCalculator(IGame const& game, ILapCalculator& lapCalculator)
    : m_game(game),
      m_lapCalculator(lapCalculator)
{
    int boostsAvailable =  m_game.boosts();
    int lapsTotal = m_game.laps();
}

bool BoostCalculator::calculateBoost() {
    int curentLap = m_lapCalculator.lap();
    return false;
}
