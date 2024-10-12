#pragma once
#include <cstddef> // IWYU pragma: export
#include <cstdint> // IWYU pragma: export
#include <ostream>

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
};

template<typename first, typename second, typename third>
struct Triple {
    using A = first;
    using B = second;
    using C = third;
    A a;
    B b;
    C c;
};

template<typename T>
struct Vec2 {
    using type = T;
    T x;
    T y;
};

template<typename T>
struct Vec3 {
    using type = T;
    T x;
    T y;
    T z;
};

template<typename T>
struct Vec4 {
    using type = T;
    T x;
    T y;
    T z;
    T w;
};

template<typename Pos_t, typename Dis_t = Pos_t>
struct Rect {
    using PositionType = Pos_t;
    using DistanceType = Dis_t;
    Pos_t x;
    Pos_t y;
    Dis_t width;
    Dis_t height;
};

template<typename T>
struct Quad {
    using type = T;
    T tl;
    T bl;
    T br;
    T tr;
};

} // namespace core

template<typename T>
std::ostream& operator<<(std::ostream& os, core::Vec2<T> c);

template<typename T>
std::ostream& operator<<(std::ostream& os, core::Vec3<T> c);

template<typename T>
std::ostream& operator<<(std::ostream& os, core::Vec4<T> c);

template<typename Pos_t, typename Dis_t>
std::ostream& operator<<(std::ostream& os, core::Rect<Pos_t, Dis_t> c);

template<typename T>
std::ostream& operator<<(std::ostream& os, core::Quad<T> c);
