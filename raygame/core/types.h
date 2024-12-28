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

template<typename first, typename second = first>
struct Pair {
    using A = first;
    using B = second;
    //NOLINTBEGIN(*-non-private-member-*)
    A a;
    B b;

    //NOLINTEND(*-non-private-member-*)

    constexpr explicit operator std::string() {
        // clang-format off
        return "Pair<"
               + core::debug::type_name<A>() + ", "
               + core::debug::type_name<B>() + ">("
               + "a: " + std::to_string(a) + ", "
               + "b: " + std::to_string(b) + ")";
        // clang-format on
    }
};

template<typename first, typename second = first, typename third = second>
struct Triple {
    using A = first;
    using B = second;
    using C = third;
    //NOLINTBEGIN(*-non-private-member-*)
    A a;
    B b;
    C c;

    //NOLINTEND(*-non-private-member-*)

    constexpr explicit operator std::string() {
        // clang-format off
        return "Triple<"
               + core::debug::type_name<A>() + ", "
               + core::debug::type_name<B>() + ", "
               + core::debug::type_name<C>() + ">("
               + "a: " + std::to_string(a) + ", "
               + "b: " + std::to_string(b) + ", "
               + "c: " + std::to_string(c) + ")";
        // clang-format on
    }
};

template<
    typename first,
    typename second = first,
    typename third  = second,
    typename fourth = third>
struct Quad {
    using A = first;
    using B = second;
    using C = third;
    using D = fourth;
    //NOLINTBEGIN(*-non-private-member-*)
    A a;
    B b;
    C c;
    D d;

    //NOLINTEND(*-non-private-member-*)

    constexpr explicit operator std::string() {
        // clang-format off
        return "Quad<"
               + core::debug::type_name<A>() + ", "
               + core::debug::type_name<B>() + ", "
               + core::debug::type_name<C>() + ">("
               + "a: " + std::to_string(a) + ", "
               + "b: " + std::to_string(b) + ", "
               + "c: " + std::to_string(c) + ","
               + "d: " + std::to_string(d) + ")";
        // clang-format on
    }
};

} // namespace core
