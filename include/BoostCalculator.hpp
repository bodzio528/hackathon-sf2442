#pragma once

#include "IBoostCalculator.hpp"

class BoostCalculator : public IBoostCalculator {
public:
    bool calculateBoost() override;
};
