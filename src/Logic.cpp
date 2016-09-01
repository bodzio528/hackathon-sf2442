#include "Logic.hpp"

#include "ICourseCalculator.hpp"
#include "IGame.hpp"

#include "Drone.hpp"

Logic::Logic(IGame& game, ICourseCalculator& calculator)
    : m_game(game),
      m_courseCalculator(calculator)
{}

Command Logic::calculateCommand() {
    IGame& game = m_game;
    Drone& me = m_game.getMyDrone();
    // detect_lap(me.nextCheckpoint);

    //select target
    auto target = game.getCheckpoint(me.nextCheckpoint);
    if (std::abs(target - me.position) < 600 + 85*std::abs(me.speed)/100) {
        auto nextCheckpoint = (me.nextCheckpoint + 1) % game.getCheckpointCount();
        target = game.getCheckpoint(nextCheckpoint);
    }

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
