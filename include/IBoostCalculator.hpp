#pragma once

class IBoostCalculator {
public:
    virtual ~IBoostCalculator() = default;

    virtual bool calculateBoost() = 0;
};
