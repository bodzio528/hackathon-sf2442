#include "BoostCalculator.hpp"

#include <gtest/gtest.h>

using namespace ::testing;

TEST(F, feil) {
    auto sut = std::make_unique<BoostCalculator>();

    EXPECT_FALSE(sut->calculateBoost());
}
