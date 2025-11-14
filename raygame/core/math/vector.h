#pragma once
#include "raygame/core/math/arithmetic.h"
#include "raygame/core/math/mathrule.h"
#include "raygame/core/types.h"
#include <concepts>
#include <string>

namespace core {

template<typename T>
struct Vec2 {
    using Type = T;

    Type m_x; // NOLINT(*-non-private-member-*)
    Type m_y; // NOLINT(*-non-private-member-*)

    constexpr Vec2() = default;

    constexpr Vec2(Type xval, Type yval)
        : m_x(xval)
        , m_y(yval) {}

    constexpr explicit operator std::string() const {
        return std::format("Vec2(x: {}, y: {})", m_x, m_y);
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr bool operator==(const Vec2<U>& other) const {
        return (std::cmp_equal(m_x, other.m_x) && std::cmp_equal(m_y, other.m_y));
    }

    template<core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<Type> operator+(std::integral auto other) {
        return {core::math::safe_add<Type>(m_x, other), core::math::safe_add<Type>(m_y, other)};
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<Type> operator+(const Vec2<U>& other) {
        return {
            core::math::safe_add<Type>(m_x, other.m_x),
            core::math::safe_add<Type>(m_y, other.m_y)
        };
    }

    template<core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<Type> operator+=(std::integral auto other) {
        return {
            m_x = core::math::safe_add<Type>(m_x, other),
            m_y = core::math::safe_add<Type>(m_y, other)
        };
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<Type> operator+=(const Vec2<U>& other) {
        return {
            m_x = core::math::safe_add<Type>(m_x, other.m_x),
            m_y = core::math::safe_add<Type>(m_y, other.m_y)
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
