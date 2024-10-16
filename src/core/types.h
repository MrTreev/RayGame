#pragma once
#include <cstddef> // IWYU pragma: export
#include <cstdint> // IWYU pragma: export
#include <string>

using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::int8_t;

using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::uint8_t;

using std::intmax_t;
using std::intptr_t;
using std::uintmax_t;
using std::uintptr_t;

using std::byte;
using std::nullptr_t;
using std::ptrdiff_t;
using std::size_t;

namespace core {

using rad_t = float;
using deg_t = float;

template<typename first, typename second>
struct Pair {
    using A = first;
    using B = second;
    A a;
    B b;

    constexpr inline operator std::string() {
        return {};
    }
};

template<typename first, typename second, typename third>
struct Triple {
    using A = first;
    using B = second;
    using C = third;
    A a;
    B b;
    C c;

    constexpr inline operator std::string() {
        return {};
    }
};

template<typename T>
struct Vec2 {
    using Type = T;
    Type x;
    Type y;

    constexpr inline operator std::string() {
        return "Vec2(x: " + x + ", y: " + y + ")";
    }
};

template<typename T>
struct Vec3 {
    using Type = T;
    Type x;
    Type y;
    Type z;

    constexpr inline operator std::string() {
        return "Vec3(x: " + x + ", y: " + y + ", z: " + z + ")";
    }
};

template<typename T>
struct Vec4 {
    using Type = T;
    Type x;
    Type y;
    Type z;
    Type w;

    constexpr inline operator std::string() {
        return "Vec4(x: " + x + ", y: " + y + ", z: " + z + ", w: " + w + ")";
    }
};

template<typename Pos_t, typename Dis_t = Pos_t>
struct Rect {
    using PositionType = Pos_t;
    using DistanceType = Dis_t;
    PositionType x;
    PositionType y;
    DistanceType width;
    DistanceType height;

    constexpr inline operator std::string() {
        return "Rect(x: " + x + ", y: " + y + ", width: " + width
               + ", height: " + height + ")";
    }
};

template<typename T>
struct Quad {
    using Type = T;
    Type tl;
    Type bl;
    Type br;
    Type tr;

    constexpr inline operator std::string() {
        return "Quad(tl: " + tl + ", bl: " + bl + ", br: " + br + ", tr: " + tr
               + ")";
    }
};

} // namespace core
