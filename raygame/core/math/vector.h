#pragma once
#include "raygame/core/math/arithmetic.h"
#include "raygame/core/math/mathrule.h"
#include "raygame/core/types.h"
#include <string>

namespace core {

template<typename T>
struct Vec2 {
    using Type = T;

    Type x; // NOLINT(*-non-private-member-*)
    Type y; // NOLINT(*-non-private-member-*)

    constexpr Vec2() = default;

    constexpr Vec2(Type xval, Type yval)
        : x(xval)
        , y(yval) {}

    constexpr explicit operator std::string() const {
        return std::format("Vec2(x: {}, y: {})", x, y);
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr bool operator==(const Vec2<U>& other) const {
        return (std::cmp_equal(x, other.x) && std::cmp_equal(y, other.y));
    }

    template<core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<Type> operator+(auto other) {
        return {core::math::safe_add<Type>(x, other), core::math::safe_add<Type>(y, other)};
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<Type> operator+(const Vec2<U>& other) {
        return {core::math::safe_add<Type>(x, other.x), core::math::safe_add<Type>(y, other.y)};
    }

    template<core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<Type> operator+=(auto other) {
        return {x = core::math::safe_add<Type>(x, other), y = core::math::safe_add<Type>(y, other)};
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<Type> operator+=(const Vec2<U>& other) {
        return {
            x = core::math::safe_add<Type>(x, other.x),
            y = core::math::safe_add<Type>(y, other.y)
        };
    }
};

extern template struct core::Vec2<uint8_t>;
extern template struct core::Vec2<uint16_t>;
extern template struct core::Vec2<uint32_t>;
extern template struct core::Vec2<uint64_t>;
extern template struct core::Vec2<int8_t>;
extern template struct core::Vec2<int16_t>;
extern template struct core::Vec2<int32_t>;
extern template struct core::Vec2<int64_t>;
} // namespace core
