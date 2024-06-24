#pragma once
#include "core/exception.h"
#include "core/logger.h"
#include "core/types.h"
#include <format>
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

class NumericCondition: public exception::detail::Condition {};

template<typename Out_T, typename In_T>
static constexpr Out_T numeric_cast(const In_T& input RG_LOC_CUR) {
    if constexpr (std::numeric_limits<In_T>::max() < std::numeric_limits<Out_T>::max()) {
        if (input > std::numeric_limits<Out_T>::max()) {
            core::log::error(std::format(
                "Input of type '{}' is above the max for output type '{}': {}",
                type_name<In_T>(),
                type_name<Out_T>(),
                input
            ) RG_LOC_VAR);
        };
    }
    if constexpr (std::numeric_limits<In_T>::min() > std::numeric_limits<Out_T>::min()) {
        if (input < std::numeric_limits<Out_T>::min()) {
            core::log::error(std::format(
                "Input of type '{}' is below the min for output type '{}': {}",
                type_name<In_T>(),
                type_name<Out_T>(),
                input
            ) RG_LOC_VAR);
        };
    }
    return static_cast<Out_T>(input);
}

} // namespace core::math
