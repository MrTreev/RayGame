#pragma once
#include "raygame/core/math/arithmetic.h"
#include "raygame/core/math/mathrule.h"
#include "raygame/core/types.h"
#include <string>

namespace core {

template<typename T>
struct Vec2 {
    using Type = T;

    // NOLINTBEGIN(*-non-private-member-*)
    Type x;
    Type y;
    // NOLINTEND(*-non-private-member-*)

    constexpr Vec2() = default;

    constexpr Vec2(Type xval, Type yval)
        : x(xval)
        , y(yval) {}

    constexpr explicit operator std::string() const {
        return "Vec2(x: " + std::to_string(x) + ", y: " + std::to_string(y)
               + ")";
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr bool operator==(const Vec2<U>& other) const {
        return (std::cmp_equal(x, other.x) && std::cmp_equal(y, other.y));
    }

    template<core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<T> operator+(auto other) {
        return {
            core::math::safe_add<T>(x, other),
            core::math::safe_add<T>(y, other)
        };
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<T> operator+(const Vec2<U>& other) {
        return {
            core::math::safe_add<T>(x, other.x),
            core::math::safe_add<T>(y, other.y)
        };
    }

    template<core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<T> operator+=(auto other) {
        return {
            x = core::math::safe_add<T>(x, other),
            y = core::math::safe_add<T>(y, other)
        };
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<T> operator+=(const Vec2<U>& other) {
        return {
            x = core::math::safe_add<T>(x, other.x),
            y = core::math::safe_add<T>(y, other.y)
        };
    }
};

// Vec2 Specialisations
extern template struct core::Vec2<uint8_t>;
extern template struct core::Vec2<uint16_t>;
extern template struct core::Vec2<uint32_t>;
extern template struct core::Vec2<uint64_t>;
extern template struct core::Vec2<int8_t>;
extern template struct core::Vec2<int16_t>;
extern template struct core::Vec2<int32_t>;
extern template struct core::Vec2<int64_t>;
} // namespace core
