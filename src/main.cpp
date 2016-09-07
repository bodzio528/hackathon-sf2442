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
#include "LongestSegmentCalculator.hpp"
#include "TargetCalculator.hpp"

int main(int ac, char *av[])
{
    Game game;
    game.initialize(std::cin);

    CourseCalculator courseCalculator(4.5);
    TargetCalculator targetCalculator(game, 550.0);

    LapCalculator lapCalculator(game);
    LongestSegmentCalculator segmentCalculator(game);
    BoostCalculator boostCalculator(game, lapCalculator, segmentCalculator);

    Logic logic(game, courseCalculator, targetCalculator, boostCalculator);

    while (1) {
        game.update(std::cin);
        lapCalculator.update();
        std::cout << logic.calculateCommand();
    }
}
