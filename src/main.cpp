#ifndef SF2442_CUMULATIVE
#include <iostream>
#include <vector>
#endif

#include "Game.hpp"
#include "Command.hpp"
#include "Logic.hpp"
#include "BoostCalculator.hpp"
#include "CourseCalculator.hpp"
#include "LapCalculator.hpp"
#include "TargetCalculator.hpp"

int main(int ac, char *av[]) {
    Game game;
    game.initialize(std::cin);

    CourseCalculator courseCalculator(3.0);
    TargetCalculator targetCalculator(game);

    LapCalculator lapCalculator(game);
    BoostCalculator boostCalculator(game, lapCalculator);

    Logic logic(game, courseCalculator, targetCalculator, boostCalculator);

    while (1) {
        game.update(std::cin);
        lapCalculator.update();
        auto cmd = logic.calculateCommand();
        std::cout << cmd;
    }
}
