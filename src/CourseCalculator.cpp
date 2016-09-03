#include "CourseCalculator.hpp"

#include "Drone.hpp"

CourseCalculator::CourseCalculator(double force) : m_correction_coefficient(force) {}

Vector CourseCalculator::calculateCorrection(Drone const& drone, Position target) {
    auto trajectory = target - drone.position;
    auto course = std::arg(trajectory);
    auto angle = course - std::arg(drone.speed);
    auto speed_parallel = std::polar(std::abs(drone.speed) * std::cos(angle), course);
    auto speed_perpendicular = drone.speed - speed_parallel;

    return -m_correction_coefficient * speed_perpendicular;
}
