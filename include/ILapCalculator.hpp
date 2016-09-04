#pragma once

class ILapCalculator
{
public:
    virtual ~ILapCalculator() = default;

    virtual int lap() const = 0;
};
