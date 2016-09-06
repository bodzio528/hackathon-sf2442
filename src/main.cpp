#ifndef SF2442_CUMULATIVE
#include <iostream>
#include <vector>
#endif

#include "BoostCalculator.hpp"
#include "Command.hpp"
#include "CourseCalculator.hpp"
#include "Game.hpp"
#include "LapCalculator.hpp"
#include "Logic.hpp"
#include "TargetCalculator.hpp"
#include "LongestSegmentCalculator.hpp"

int main(int ac, char *av[])
{
    Game game;
    game.initialize(std::cin);

    CourseCalculator courseCalculator(4.5);
    TargetCalculator targetCalculator(game);

    LapCalculator lapCalculator(game);
    LongestSegmentCalculator segmentCalculator(game);
    BoostCalculator boostCalculator(game, lapCalculator, segmentCalculator);

    Logic logic(game, courseCalculator, targetCalculator, boostCalculator);

    while (1) {
        game.update(std::cin);
        lapCalculator.update();
        auto cmd = logic.calculateCommand();
        std::cout << cmd;
    }
}
