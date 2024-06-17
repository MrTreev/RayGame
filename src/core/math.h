#pragma once
#include "core/condition.h"
#include "core/types.h"
#include <format>
#include <limits>
#include <typeinfo>

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

template<typename Out_T, typename In_T>
constexpr Out_T numeric_cast(const In_T& input) {
    const auto max_val = std::numeric_limits<Out_T>::max();
    const auto min_val = std::numeric_limits<Out_T>::min();
    condition::pre_condition(
        (input <= max_val),
        std::format(
            "Input of type {} is above the max for output type {}",
            typeid(In_T).name(),
            typeid(Out_T).name()
        )
    );
    condition::pre_condition(
        (input >= min_val),
        std::format(
            "Input of type {} is below the min for output type {}",
            typeid(In_T).name(),
            typeid(Out_T).name()
        )
    );
    return static_cast<Out_T>(input);
}

} // namespace core::math
