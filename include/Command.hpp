#pragma once

#ifndef SF2442_CUMULATIVE
#include <ostream>
#endif

#include "Geometry.hpp"

struct Command
{
    Position target;
    std::string thrust;

    friend std::ostream& operator<<(std::ostream& out, Command c)
    {
        return out << static_cast<int>(c.target.real()) << " " << static_cast<int>(c.target.imag()) << " " << c.thrust
                   << std::endl;
    }
};
