#include "core/math.h" // IWYU pragma: keep
#include <random>

std::random_device dev;
std::mt19937       core::math::detail::rng(dev());
