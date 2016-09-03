#ifndef SF2442_CUMULATIVE
#include <iostream>
#include <vector>
#endif

#include "Game.hpp"
#include "Command.hpp"
#include "Logic.hpp"
#include "CourseCalculator.hpp"
#include "TargetCalculator.hpp"

int main(int ac, char *av[]) {
    Game game;
    game.initialize(std::cin);

    CourseCalculator courseCalculator(3.0);
    TargetCalculator targetCalculator(game);

    Logic logic(game, courseCalculator, targetCalculator);

    while (1) {
        game.update(std::cin);
        auto cmd = logic.calculateCommand();
        std::cout << cmd;
    }
}
