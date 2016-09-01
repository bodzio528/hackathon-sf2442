#pragma once

#include "Geometry.hpp"

struct Command {
    Position target;
    std::string thrust;

    friend std::ostream& operator<<(std::ostream& out, Command c) {
        return out << c.target.real() << " " << c.target.imag() << " "  << c.thrust << std::endl;
    }
};
