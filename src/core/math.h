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

inline constexpr core::rad_t deg2rad(core::deg_t deg) {
    return deg * constants::deg2rad;
};

inline constexpr core::deg_t rad2deg(core::rad_t rad) {
    return rad * constants::rad2deg;
};

template<typename Out_T, typename In_T>
inline constexpr Out_T numeric_cast(const In_T& input RG_LOC_CUR) {
    const auto max_val = std::numeric_limits<Out_T>::max();
    const auto min_val = std::numeric_limits<Out_T>::min();
    condition::pre_condition(
        (input <= max_val),
        std::format(
            "Input of type {} is above the max for output type {}",
            typeid(In_T).name(),
            typeid(Out_T).name()
        ) RG_LOC_VAR
    );
    condition::pre_condition(
        (input >= min_val),
        std::format(
            "Input of type {} is below the min for output type {}",
            typeid(In_T).name(),
            typeid(Out_T).name()
        ) RG_LOC_VAR
    );
    return static_cast<Out_T>(input);
}

} // namespace core::math
