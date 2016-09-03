#pragma once

#include "ITargetCalculator.hpp"

class IGame;

class TargetCalculator : public ITargetCalculator {
public:
    TargetCalculator(IGame&);

    Position calculateTarget(Drone const&) override;

private:
    IGame& m_game;
};
