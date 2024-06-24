#pragma once
#include <cstddef> // IWYU pragma: export
#include <cstdint> // IWYU pragma: export

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

// NOLINTBEGIN(readability-identifier-naming)
template<typename T>
struct Vec2 {
    T x;
    T y;
};

template<typename T>
struct Vec3 {
    T x;
    T y;
    T z;
};

template<typename T>
struct Vec4 {
    T x;
    T y;
    T z;
    T w;
};

template<typename Pos_t, typename Dis_t = Pos_t>
struct Rect {
    Pos_t x;
    Pos_t y;
    Dis_t width;
    Dis_t height;
};

template<typename T>
struct Quad {
    T tl;
    T bl;
    T br;
    T tr;
};
// NOLINTEND(readability-identifier-naming)
//
} // namespace core
