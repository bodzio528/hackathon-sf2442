#include "Logic.hpp"

#include "IBoostCalculator.hpp"
#include "ICourseCalculator.hpp"
#include "IGame.hpp"
#include "ITargetCalculator.hpp"

#include "Drone.hpp"

Logic::Logic(IGame& game,
        ICourseCalculator& courseCalc,
        ITargetCalculator& targetCalc,
        IBoostCalculator& boostCalc)
    : m_game(game),
      m_courseCalculator(courseCalc),
      m_targetCalculator(targetCalc),
      m_boostCalculator(boostCalc)
{
}

Command Logic::calculateCommand()
{
    Command cmd;

    Drone const& drone = m_game.drone();

    cmd.target = m_targetCalculator.calculateTarget(drone);
    cmd.target += m_courseCalculator.calculateCorrection(drone, cmd.target);

    cmd.thrust = "100";
    if (m_boostCalculator.calculateBoost()) {
        cmd.thrust = "BOOST";
    }

    return cmd;
}
