#include <iostream>
#include <string>
#include <memory>

#include "Game.hpp"
#include "Command.hpp"
#include "Logic.hpp"
#include "CourseCalculator.hpp"

bool almost_prallel(Vector a, Vector b) {
    return std::abs(a.real()*b.real() + a.imag()*b.imag() - std::abs(a)*std::abs(b)) < 1;
}

void detect_lap(int checkpoint) {
    static int current_checkpoint = 0;
    static bool last_checkpoint = false;

    if (checkpoint != current_checkpoint) {
        std::cerr << "checkpoint changed" << std::endl;
        if (checkpoint == 0) {
            std::cerr << "ostatnia prosta" << std::endl;
        }
        // lap detected??
        current_checkpoint = checkpoint;
    }
}

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