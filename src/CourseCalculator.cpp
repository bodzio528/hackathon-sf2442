#include "CourseCalculator.hpp"

#include "Drone.hpp"

namespace {
double scalar_product(Vector a, Vector b) {
    return a.real()*b.real() + a.imag()*b.imag();
}

Vector map_vector(Vector a, Vector b) {
    return scalar_product(a, b) * b / std::pow(std::abs(b), 2.0);
}
}

Vector CourseCalculator::calculateCorrection(Drone const& drone, Position target) {
    return - drone.speed + map_vector(drone.speed, target - drone.position);
}
