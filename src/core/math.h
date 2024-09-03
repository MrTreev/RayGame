#pragma once
#include "core/config.h"
#include "core/exception.h"
#include "core/types.h"
#include <concepts>
#include <format>
#include <limits>
#include <utility>

#if defined(RAYGAME_CC_GCC) || defined(RAYGAME_CC_CLANG)
#    include <cxxabi.h>
#    include <typeinfo>
#endif

template<typename T>
inline constexpr std::string type_name() {
    int         status = 0;
    std::string tname  = typeid(T).name();
#if defined(RAYGAME_CC_GCC) || defined(RAYGAME_CC_CLANG)
    char* demangled_name =
        abi::__cxa_demangle(tname.c_str(), nullptr, nullptr, &status);
    if (status == 0) {
        tname = demangled_name;
        free(demangled_name);
    }
#endif
    return tname;
}

namespace core::math {

namespace constants {
constexpr float pi      = 3.14159265358979323846F;
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
requires std::integral<Out_T> && std::integral<In_T>
inline constexpr Out_T numeric_cast(In_T input) {
    if (std::in_range<Out_T>(input)) {
        return static_cast<Out_T>(input);
    }
    throw exception::Condition(std::format(
        "Input of type '{}' is above the max for output type '{}': "
        "{}",
        type_name<In_T>(),
        type_name<Out_T>(),
        input
    ));
}

} // namespace core::math
