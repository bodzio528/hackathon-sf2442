#pragma once

#ifndef SF2442_CUMULATIVE
#include <complex>
#endif

using Position = std::complex<double>;
using Speed = std::complex<double>;
using Vector = std::complex<double>;

constexpr Position c_origin = {0, 0};
constexpr Speed c_static = {0, 0};
constexpr Vector c_zero = {0, 0};

inline Vector normalize(Vector const& a)
{
    return a / std::abs(a);
}

inline double dot(Vector const& a, Vector const& b)
{
    return a.real() * b.real() + a.imag() * b.imag();
}
