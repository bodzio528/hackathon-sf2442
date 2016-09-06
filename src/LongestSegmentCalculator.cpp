#include "LongestSegmentCalculator.hpp"

#include "IGame.hpp"

LongestSegmentCalculator::LongestSegmentCalculator(IGame const& game) : m_game(game)
{
}

int LongestSegmentCalculator::longestSegment() const
{
    std::pair<double, int> segmentFound = std::make_pair(0.0, 0);

    auto checkpoints = m_game.checkpoints();
    if (checkpoints > 2) {
        Position first = m_game.checkpoint(0);
        Position prev = first;

        for (int i = 1; i < checkpoints; ++i) {
            auto curr = m_game.checkpoint(i);
            auto length = std::norm(curr - prev);

            if (segmentFound.first < length){
                segmentFound = std::make_pair(length, i);
            }

            prev = curr;
        }
        auto length = std::norm(first - prev);

        if (segmentFound.first < length){
            //heil new king 0! without it, if last is longest, then second-largest is returned
            segmentFound = std::make_pair(0.0, 0);
        }
    }

    return segmentFound.second;
}
