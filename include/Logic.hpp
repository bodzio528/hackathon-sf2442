#pragma once

#include "Command.hpp"

class IGame;
class ICourseCalculator;

class Logic {
public:
    Logic(IGame& game, ICourseCalculator& calculator);

    Command calculateCommand();
private:
    IGame& m_game;
    ICourseCalculator& m_courseCalculator;

    bool boost_available = true;
};
