#include "CourseCalculator.hpp"

#include "Drone.hpp"

CourseCalculator::CourseCalculator(double efficiency)
    : m_correction_coefficient(efficiency)
{
}

Vector CourseCalculator::calculateCorrection(
        Drone const& drone, Position target)
{
    auto route = target - drone.position;

    auto speed_parallel = route * dot(drone.speed, route) / std::norm(route);
    auto speed_perpendicular = drone.speed - speed_parallel;

    return -m_correction_coefficient * speed_perpendicular;
}
