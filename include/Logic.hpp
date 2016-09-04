#pragma once

#include "Command.hpp"

class IGame;

class IBoostCalculator;
class ICourseCalculator;
class ITargetCalculator;

class Logic
{
public:
    Logic(IGame&, ICourseCalculator&, ITargetCalculator&, IBoostCalculator&);

    Command calculateCommand();

private:
    IGame& m_game;
    ICourseCalculator& m_courseCalculator;
    ITargetCalculator& m_targetCalculator;
    IBoostCalculator& m_boostCalculator;
};
