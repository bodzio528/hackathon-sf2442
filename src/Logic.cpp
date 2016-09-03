#include "Logic.hpp"

#include "IGame.hpp"
#include "ICourseCalculator.hpp"
#include "ITargetCalculator.hpp"

#include "Drone.hpp"

Logic::Logic(IGame& game, ICourseCalculator& courseCalc, ITargetCalculator& targetCalc)
    : m_game(game),
      m_courseCalculator(courseCalc),
      m_targetCalculator(targetCalc)
{}

Command Logic::calculateCommand() {
    IGame& game = m_game;
    Drone& me = m_game.getMyDrone();

    auto target = m_targetCalculator.calculateTarget(me);
    target += m_courseCalculator.calculateCorrection(me, target);

    std::string thrust = "100";
    auto course = target - me.position;
    if (std::abs(course) > 3000) {
        // even more speed
        if ((game.getRemainingBoost() > 2 or me.nextCheckpoint == 0) and boost_available) {
            thrust = game.useBoost();
        }
    }

    return Command{target, thrust};
}
