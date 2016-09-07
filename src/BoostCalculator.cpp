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

    auto move_boost = [this, &boosts_available](
            int lap, int checkpoint) -> void {
        m_boosts.insert(std::make_pair(lap, checkpoint));
        --boosts_available;
    };

    // last straight reserve
    move_boost(laps, 0);

    // longest segment of each
    for (int lap = laps; boosts_available and lap > 0; --lap) {
        move_boost(lap, segment);
    }

    // spectacular finish
    while (boosts_available) {
        move_boost(laps, 0);
    }
}

int BoostCalculator::calculateBoost()
{
    auto range = m_boosts.equal_range(
            std::make_pair(m_lapCalculator.lap(), m_drone.nextCheckpoint));
    auto boosts_available = std::distance(range.first, range.second);

    if (boosts_available) {
        m_boosts.erase(range.first);
    }

    return boosts_available;
}
