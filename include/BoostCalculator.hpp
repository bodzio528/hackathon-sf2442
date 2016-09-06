#pragma once

#include "IBoostCalculator.hpp"

#ifndef SF2442_CUMULATIVE
#include <set>
#endif

class Drone;

class IGame;
class ILapCalculator;
class ILongestSegmentCalculator;

class BoostCalculator : public IBoostCalculator
{
public:
    BoostCalculator(IGame const&, ILapCalculator const&, ILongestSegmentCalculator const&);

    bool calculateBoost() override;

private:
    Drone const& m_drone;
    ILapCalculator const& m_lapCalculator;

    std::set<std::pair<int, int>> m_boosts;
};
