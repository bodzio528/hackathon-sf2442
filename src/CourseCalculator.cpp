#include "CourseCalculator.hpp"

#include "Drone.hpp"

namespace {
int scalar_product(Vector a, Vector b) {
    return a.real()*b.real() + a.imag()*b.imag();
}

Vector map_vector(Vector a, Vector b) {
    return scalar_product(a, b) * b / std::abs(b) / std::abs(b);
}
}

Vector CourseCalculator::calculateCorrection(Drone const& drone, Position target) {
    return - drone.speed + map_vector(drone.speed, target - drone.position);
}
