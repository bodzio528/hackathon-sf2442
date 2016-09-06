#pragma once

#include "ILongestSegmentCalculator.hpp"

class IGame;

class LongestSegmentCalculator : public ILongestSegmentCalculator
{
public:
    LongestSegmentCalculator(IGame const&);

    int longestSegment() const override;

private:
    IGame const& m_game;
};
