#include "Logic.hpp"

#include "IGame.hpp"
#include "IBoostCalculator.hpp"
#include "ICourseCalculator.hpp"
#include "ITargetCalculator.hpp"

#include "Drone.hpp"

Logic::Logic(
        IGame& game,
        ICourseCalculator& courseCalc,
        ITargetCalculator& targetCalc,
        IBoostCalculator& boostCalc)
    : m_game(game),
      m_courseCalculator(courseCalc),
      m_targetCalculator(targetCalc),
      m_boostCalculator(boostCalc)
{}

Command Logic::calculateCommand() {
    Drone const& me = m_game.getMyDrone();

    auto target = m_targetCalculator.calculateTarget(me);
    target += m_courseCalculator.calculateCorrection(me, target);

    std::string thrust = "100";
    if (m_boostCalculator.calculateBoost()) {
        thrust = "BOOST";
    }

    return Command{target, thrust};
}
