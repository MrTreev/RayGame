#pragma once
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

inline constexpr core::rad_t deg2rad(core::deg_t deg) {
    return deg * constants::deg2rad;
};

inline constexpr core::deg_t rad2deg(core::rad_t rad) {
    return rad * constants::rad2deg;
};

class NumericException: public std::exception {};

template<typename Out_T, typename In_T>
inline constexpr Out_T numeric_cast(const In_T& input RG_LOC_CUR) {
    if (input > std::numeric_limits<Out_T>::max()) {
        core::log::error(std::format(
            "Input of type {} is above the max for output type {}",
            type_name<In_T>(),
            type_name<Out_T>()
        ) RG_LOC_VAR);
        throw NumericException();
    };
    if (input < std::numeric_limits<Out_T>::min()) {
        core::log::error(std::format(
            "Input of type {} is below the min for output type {}",
            type_name<In_T>(),
            type_name<Out_T>()
        ) RG_LOC_VAR);
        throw NumericException();
    };
    return static_cast<Out_T>(input);
}

} // namespace core::math
