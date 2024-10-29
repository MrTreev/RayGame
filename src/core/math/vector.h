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

    operator std::string();

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    Vec2<T> operator+(U other) {
        return {
            core::math::safe_add<T>(x, other),
            core::math::safe_add<T>(y, other)
        };
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    Vec2<T> operator+(Vec2<U> other) {
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

    operator std::string();

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    Vec3<T> operator+(U other) {
        return {
            core::math::safe_add<T>(x, other),
            core::math::safe_add<T>(y, other),
            core::math::safe_add<T>(z, other)
        };
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    Vec3<T> operator+(Vec3<U> other) {
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

    operator std::string();

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    Vec4<T> operator+(U other) {
        return {
            core::math::safe_add<T>(x, other),
            core::math::safe_add<T>(y, other),
            core::math::safe_add<T>(z, other),
            core::math::safe_add<T>(w, other)
        };
    }

    template<typename U, core::math::MathRule MR = core::math::MR_DEFAULT>
    Vec4<T> operator+(Vec4<U> other) {
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
