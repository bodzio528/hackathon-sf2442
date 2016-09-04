#include "Command.hpp"

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace ::testing;

struct CommandTestSuite : Test
{
    Command sut;
};

TEST_F(CommandTestSuite, commandIsPrintable)
{
    sut.target = Position{2406, 1271};
    sut.thrust = "73";

    std::stringstream ss;
    ss << sut;

    EXPECT_THAT(ss.str(), StartsWith("2406 1271 73"));
    EXPECT_THAT(ss.str(), EndsWith("\n"));
}

TEST_F(CommandTestSuite, commandIsPrintable_BOOST)
{
    sut.target = Position{2486, 1571};
    sut.thrust = "BOOST";

    std::stringstream ss;
    ss << sut;

    EXPECT_THAT(ss.str().c_str(), StartsWith("2486 1571 BOOST"));
    EXPECT_THAT(ss.str(), EndsWith("\n"));
}
