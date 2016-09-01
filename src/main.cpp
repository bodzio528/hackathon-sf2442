
#ifndef AAA
#include <iostream>
#include <vector>
#endif

#include "Game.hpp"
#include "Command.hpp"
#include "Logic.hpp"
#include "CourseCalculator.hpp"

int main()
{
    Game g;
    g.initialize(std::cin);

    CourseCalculator c;

    Logic l(g, c);

    while (1) {
        g.update(std::cin);
        auto cmd = l.calculateCommand();
        std::cout << cmd;
    }
}
