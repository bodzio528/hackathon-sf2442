#pragma once

class IBoostCalculator
{
public:
    virtual ~IBoostCalculator() = default;

    virtual int calculateBoost() = 0;
};
