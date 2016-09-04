#pragma once

#include "ILapCalculator.hpp"

class IGame;

class LapCalculator : public ILapCalculator
{
public:
    LapCalculator(IGame const& game);

    void update();

    int lap() const override;

private:
    IGame const& m_game;

    int m_leap = 0;
    int m_nextCheckpoint = 0;
};
