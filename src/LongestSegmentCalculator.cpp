#include "LongestSegmentCalculator.hpp"

#include "IGame.hpp"

#ifndef SF2442_CUMULATIVE
#include <algorithm>
#include <set>
#endif

LongestSegmentCalculator::LongestSegmentCalculator(IGame const& game)
    : m_game(game)
{
}

int LongestSegmentCalculator::longestSegment() const
{
    auto checkpoints = m_game.checkpoints();
    if (checkpoints < 3) {
        return 0;
    }

    std::set<std::pair<double, int>> segments;

    if (checkpoints > 2) {
        Position first = m_game.checkpoint(0);
        Position start = first;

        for (int i = 1; i < checkpoints; ++i) {
            Position end = m_game.checkpoint(i);
            segments.emplace(std::make_pair(std::norm(end - start), i));
            start = end;
        }

        segments.emplace(std::make_pair(std::norm(first - start), 0));
    }

    return std::max_element(segments.cbegin(), segments.cend())->second;
}
