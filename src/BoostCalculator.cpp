#include "BoostCalculator.hpp"

#include "IGame.hpp"
#include "ILapCalculator.hpp"
#include "ILongestSegmentCalculator.hpp"

#include "Drone.hpp"

BoostCalculator::BoostCalculator(IGame const& game,
        const ILapCalculator& lapCalc,
        ILongestSegmentCalculator const& segmentCalc)
    : m_drone(game.drone()), m_lapCalculator(lapCalc)
{
    int boosts_available = game.boosts();
    int laps = game.laps();
    int segment = segmentCalc.longestSegment();

    auto move_boost = [this](int lap, int checkpoint) -> int {
        return m_boosts.insert(std::make_pair(lap, checkpoint)).second & 1;
    };

    // last straight
    boosts_available -= move_boost(laps, 0);

    for (int lap = laps; (lap > 0) and boosts_available; --lap) {
        boosts_available -= move_boost(lap, segment);
    }
}

bool BoostCalculator::calculateBoost()
{
    int lap = m_lapCalculator.lap();
    int checkpoint = m_drone.nextCheckpoint;

    const auto it = m_boosts.find(std::make_pair(lap, checkpoint));
    if (it != m_boosts.end()) {
        m_boosts.erase(it);
        return true;
    }
    return false;
}
