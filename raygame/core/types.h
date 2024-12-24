#pragma once
#include "raygame/core/debug.h"
#include <cstddef> // IWYU pragma: export
#include <cstdint> // IWYU pragma: export
#include <string>

namespace core {

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

using rad_t = float;
using deg_t = float;

template<typename first, typename second>
struct Pair {
    using A = first;
    using B = second;
    A a;
    B b;

    constexpr operator std::string() {
        return "Pair<" + core::debug::type_name<A>() + ", "
               + core::debug::type_name<B>() + ">(" + ": " + std::to_string(a)
               + ", " + ": " + std::to_string(b) + ")";
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

    constexpr operator std::string() {
        return "Triple<" + core::debug::type_name<A>() + ", "
               + core::debug::type_name<B>() + ", "
               + core::debug::type_name<C>() + ">(" + ": " + std::to_string(a)
               + ", " + ": " + std::to_string(b) + ", " + ": "
               + std::to_string(c) + ")";
    }
};

template<typename T>
struct Quad {
    static_assert(std::is_integral<T>() || std::is_floating_point<T>());
    using Type = T;
    Type tl;
    Type bl;
    Type br;
    Type tr;

    constexpr operator std::string() {
        return "Quad<" + core::debug::type_name<Type>() + ">(tl: "
               + std::to_string(tl) + ", bl: " + std::to_string(bl) + ", br: "
               + std::to_string(br) + ", tr: " + std::to_string(tr) + ")";
    }
};

extern template struct Quad<uint8_t>;
extern template struct Quad<uint16_t>;
extern template struct Quad<uint32_t>;
extern template struct Quad<uint64_t>;
extern template struct Quad<int8_t>;
extern template struct Quad<int16_t>;
extern template struct Quad<int32_t>;
extern template struct Quad<int64_t>;

} // namespace core
