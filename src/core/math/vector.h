#pragma once
#include "core/base/types.h"
#include <string>

namespace core {

template<typename T>
struct Vec2 {
    using Type = T;
    Type x;
    Type y;

    operator std::string();
};

template<typename T>
struct Vec3 {
    using Type = T;
    Type x;
    Type y;
    Type z;

    operator std::string();
};

template<typename T>
struct Vec4 {
    using Type = T;
    Type x;
    Type y;
    Type z;
    Type w;

    operator std::string();
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
