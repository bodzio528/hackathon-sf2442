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

    std::string thrust = "100";

    //select target
    auto target = game.getCheckpoint(me.nextCheckpoint);
    if (std::abs(target - me.position) < 600 + 85*std::abs(me.speed)/100) {
        auto nextCheckpoint = (me.nextCheckpoint + 1) % game.getCheckpointCount();
        target = game.getCheckpoint(nextCheckpoint);
    }

//    target += m_courseCalculator.calculateCorrection(me, target);

    auto course = target - me.position;
    // apply course correction
    if (std::abs(me.speed) > 50) {
        course = course - 3*me.speed;
        target = me.position + course;
    }
    if (std::abs(course) > 3000) {
        // even more speed
        if ((game.getRemainingBoost() > 2 or me.nextCheckpoint == 0) and boost_available) {
            thrust = game.useBoost();
        }
    }

    return Command{target, thrust};
}
