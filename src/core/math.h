#pragma once
#include "core/logger.h"
#include "core/types.h"
#include <limits>

#if defined(RAYGAME_CC_GCC) || defined(RAYGAME_CC_CLANG)
#    include <cxxabi.h>
#    include <typeinfo>

template<typename T>
inline constexpr std::string type_name() {
    int         status = 0;
    std::string tname  = typeid(T).name();
    char*       demangled_name =
        abi::__cxa_demangle(tname.c_str(), nullptr, nullptr, &status);
    if (status == 0) {
        tname = demangled_name;
        std::free(demangled_name); //NOLINT
    }
    return tname;
}
#endif

namespace core::math {

namespace constants {
constexpr float pi      = 3.14159265358979323846F; // NOLINT
constexpr float deg2rad = (pi / 180.0F);
constexpr float rad2deg = (180.0F / pi);
constexpr float epsilon = 0.000001F;
} // namespace constants

static constexpr core::rad_t deg2rad(core::deg_t deg) {
    return deg * constants::deg2rad;
};

static constexpr core::deg_t rad2deg(core::rad_t rad) {
    return rad * constants::rad2deg;
};

template<typename Out_T, typename In_T>
static constexpr Out_T numeric_cast(const In_T& input RG_LOC_CUR) {
    constexpr auto in_max  = std::numeric_limits<In_T>::max();
    constexpr auto in_min  = std::numeric_limits<In_T>::min();
    constexpr auto out_max = std::numeric_limits<Out_T>::max();
    constexpr auto out_min = std::numeric_limits<Out_T>::min();

    if constexpr (in_max < out_max) {
        if (input > out_max) {
            core::log::error(
                "Input of type '{}' is above the max for output type '{}': {}",
                type_name<In_T>(),
                type_name<Out_T>(),
                input RG_LOC_VAR
            );
        };
    }
    if constexpr (in_min > out_min) {
        if (input < out_min) {
            core::log::error(
                "Input of type '{}' is below the min for output type '{}': {}",
                type_name<In_T>(),
                type_name<Out_T>(),
                input RG_LOC_VAR
            );
        };
    }
    return static_cast<Out_T>(input);
}

} // namespace core::math
