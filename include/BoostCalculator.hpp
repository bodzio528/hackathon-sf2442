#pragma once

#include "IBoostCalculator.hpp"

class IGame;
class ILapCalculator;

class BoostCalculator : public IBoostCalculator
{
public:
    BoostCalculator(IGame const&, ILapCalculator&);

    bool calculateBoost() override;

private:
    IGame const& m_game;
    ILapCalculator& m_lapCalculator;
};
