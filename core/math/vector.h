#pragma once
#include "core/base/types.h"
#include "core/math/arithmetic.h"
#include "core/math/mathrule.h"
#include <string>

namespace core {

template<typename T>
struct Vec2 {
    using Type = T;

    Type x;
    Type y;

    constexpr Vec2() = default;

    constexpr Vec2(Type x_, Type y_)
        : x(x_)
        , y(y_) {}

    constexpr operator std::string();

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<T> operator+(U other) {
        return {
            core::math::safe_add<T>(x, other),
            core::math::safe_add<T>(y, other)
        };
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec2<T> operator+(Vec2<U> other) {
        return {
            core::math::safe_add<T>(x, other.x),
            core::math::safe_add<T>(y, other.y)
        };
    }
};

template<typename T>
struct Vec3 {
    using Type = T;
    Type x;
    Type y;
    Type z;

    constexpr Vec3() = default;

    constexpr Vec3(Type x_, Type y_, Type z_)
        : x(x_)
        , y(y_)
        , z(z_) {}

    constexpr operator std::string();

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec3<T> operator+(U other) {
        return {
            core::math::safe_add<T>(x, other),
            core::math::safe_add<T>(y, other),
            core::math::safe_add<T>(z, other)
        };
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec3<T> operator+(Vec3<U> other) {
        return {
            core::math::safe_add<T>(x, other.x),
            core::math::safe_add<T>(y, other.y),
            core::math::safe_add<T>(z, other.z)
        };
    }
};

template<typename T>
struct Vec4 {
    using Type = T;
    Type x;
    Type y;
    Type z;
    Type w;

    constexpr Vec4() = default;

    constexpr Vec4(Type x_, Type y_, Type z_, Type w_)
        : x(x_)
        , y(y_)
        , z(z_)
        , w(w_) {}

    constexpr Vec4(Vec2<Type> vec_a, Vec2<Type> vec_b)
        : x(vec_a.x)
        , y(vec_a.y)
        , z(vec_b.x)
        , w(vec_b.y) {}

    constexpr operator std::string();

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec4<T> operator+(U other) {
        return {
            core::math::safe_add<T>(x, other),
            core::math::safe_add<T>(y, other),
            core::math::safe_add<T>(z, other),
            core::math::safe_add<T>(w, other)
        };
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    constexpr Vec4<T> operator+(Vec4<U> other) {
        return {
            core::math::safe_add<T>(x, other.x),
            core::math::safe_add<T>(y, other.y),
            core::math::safe_add<T>(z, other.z),
            core::math::safe_add<T>(w, other.w)
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

// Vec3 Specialisations
extern template struct core::Vec3<uint8_t>;
extern template struct core::Vec3<uint16_t>;
extern template struct core::Vec3<uint32_t>;
extern template struct core::Vec3<uint64_t>;
extern template struct core::Vec3<int8_t>;
extern template struct core::Vec3<int16_t>;
extern template struct core::Vec3<int32_t>;
extern template struct core::Vec3<int64_t>;

// Vec4 Specialisations
extern template struct core::Vec4<uint8_t>;
extern template struct core::Vec4<uint16_t>;
extern template struct core::Vec4<uint32_t>;
extern template struct core::Vec4<uint64_t>;
extern template struct core::Vec4<int8_t>;
extern template struct core::Vec4<int16_t>;
extern template struct core::Vec4<int32_t>;
extern template struct core::Vec4<int64_t>;

} // namespace core
