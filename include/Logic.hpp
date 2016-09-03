#pragma once

#include "Command.hpp"

class IGame;
class ICourseCalculator;
class ITargetCalculator;

class Logic {
public:
    Logic(IGame&, ICourseCalculator&, ITargetCalculator&);

    Command calculateCommand();

private:
    IGame& m_game;
    ICourseCalculator& m_courseCalculator;
    ITargetCalculator& m_targetCalculator;

    bool boost_available = true;
};
