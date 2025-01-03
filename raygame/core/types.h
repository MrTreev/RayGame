#pragma once
#include "raygame/core/debug.h"
#include <cstddef> // IWYU pragma: export
#include <cstdint> // IWYU pragma: export
#include <format>
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
        return std::format(
            "Pair<{}, {}>(a: {}, b: {})",
            core::debug::type_name<A>(),
            core::debug::type_name<B>(),
            a,
            b
        );
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
        return std::format(
            "Triple<{}, {}, {}>(a: {}, b: {}, c: {})",
            core::debug::type_name<A>(),
            core::debug::type_name<B>(),
            core::debug::type_name<C>(),
            a,
            b,
            c
        );
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
        return std::format(
            "Quad<{}, {}, {}, {}>(a: {}, b: {}, c: {}, d: {})",
            core::debug::type_name<A>(),
            core::debug::type_name<B>(),
            core::debug::type_name<C>(),
            core::debug::type_name<D>(),
            a,
            b,
            c,
            d
        );
    }
};

} // namespace core
