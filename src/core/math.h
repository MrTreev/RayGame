#pragma once
#include "core/types.h"

namespace core::math {

namespace constants {
constexpr float pi      = 3.14159265358979323846F; // NOLINT
constexpr float deg2rad = (pi / 180.0F);
constexpr float rad2deg = (180.0F / pi);
constexpr float epsilon = 0.000001F;
} // namespace constants

inline rad_t deg2rad(deg_t deg) {
    return deg * constants::deg2rad;
};

inline deg_t rad2deg(rad_t rad) {
    return rad * constants::rad2deg;
};

} // namespace core::math
