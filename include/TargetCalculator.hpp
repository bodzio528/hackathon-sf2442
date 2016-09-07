#pragma once

#include "ITargetCalculator.hpp"

class IGame;

class TargetCalculator : public ITargetCalculator
{
public:
    TargetCalculator(IGame&, double radius);

    Position calculateTarget(Drone const&) override;

private:
    IGame& m_game;
    const double m_radius;
};
