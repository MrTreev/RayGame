#pragma once
#include "raygame/core/config.h"
#include "raygame/core/debug.h"
#include <cstddef>
#include <cstdint>
#include <format>
#include <sstream>
#include <string>
#include <type_traits>

#define RAYGAME_MAKE_FORMAT_TEMPLATE_1(classname)                              \
    template<typename TNAME>                                                   \
    struct std::formatter<classname<TNAME>, char> {                            \
        template<typename ParseContext>                                        \
        constexpr ParseContext::iterator parse(ParseContext& ctx) {            \
            auto iter = ctx.begin();                                           \
            if (iter == ctx.end()) {                                           \
                return iter;                                                   \
            }                                                                  \
            if (iter != ctx.end() && *iter != '}') {                           \
                throw std::format_error("Invalid format args for classname."); \
            }                                                                  \
            return iter;                                                       \
        }                                                                      \
        template<class FmtContext>                                             \
        FmtContext::iterator                                                   \
        format(classname<TNAME> classitem, FmtContext& ctx) const {            \
            std::ostringstream out{std::string(classitem)};                    \
            return std::ranges::copy(std::move(out).str(), ctx.out()).out;     \
        }                                                                      \
    };

#define RAYGAME_MAKE_FORMAT_TEMPLATE_2(classname)                              \
    template<typename FIRST, typename SECOND>                                  \
    struct std::formatter<classname<FIRST, SECOND>, char> {                    \
        template<typename ParseContext>                                        \
        constexpr ParseContext::iterator parse(ParseContext& ctx) {            \
            auto iter = ctx.begin();                                           \
            if (iter == ctx.end()) {                                           \
                return iter;                                                   \
            }                                                                  \
            if (iter != ctx.end() && *iter != '}') {                           \
                throw std::format_error("Invalid format args for classname."); \
            }                                                                  \
            return iter;                                                       \
        }                                                                      \
        template<class FmtContext>                                             \
        FmtContext::iterator                                                   \
        format(classname<FIRST, SECOND> classitem, FmtContext& ctx) const {    \
            std::ostringstream out{std::string(classitem)};                    \
            return std::ranges::copy(std::move(out).str(), ctx.out()).out;     \
        }                                                                      \
    };

#define RAYGAME_MAKE_FORMAT_TEMPLATE_3(classname)                              \
    template<typename FIRST, typename SECOND, typename THIRD>                  \
    struct std::formatter<classname<FIRST, SECOND, THIRD>, char> {             \
        template<typename ParseContext>                                        \
        constexpr ParseContext::iterator parse(ParseContext& ctx) {            \
            auto iter = ctx.begin();                                           \
            if (iter == ctx.end()) {                                           \
                return iter;                                                   \
            }                                                                  \
            if (iter != ctx.end() && *iter != '}') {                           \
                throw std::format_error("Invalid format args for classname."); \
            }                                                                  \
            return iter;                                                       \
        }                                                                      \
        template<class FmtContext>                                             \
        FmtContext::iterator format(                                           \
            classname<FIRST, SECOND, THIRD> classitem,                         \
            FmtContext&                     ctx                                \
        ) const {                                                              \
            std::ostringstream out{std::string(classitem)};                    \
            return std::ranges::copy(std::move(out).str(), ctx.out()).out;     \
        }                                                                      \
    };

#define RAYGAME_MAKE_FORMAT_TEMPLATE_4(classname)                              \
    template<typename FIRST, typename SECOND, typename THIRD, typename FOUR>   \
    struct std::formatter<classname<FIRST, SECOND, THIRD, FOUR>, char> {       \
        template<typename ParseContext>                                        \
        constexpr ParseContext::iterator parse(ParseContext& ctx) {            \
            auto iter = ctx.begin();                                           \
            if (iter == ctx.end()) {                                           \
                return iter;                                                   \
            }                                                                  \
            if (iter != ctx.end() && *iter != '}') {                           \
                throw std::format_error("Invalid format args for classname."); \
            }                                                                  \
            return iter;                                                       \
        }                                                                      \
        template<class FmtContext>                                             \
        FmtContext::iterator format(                                           \
            classname<FIRST, SECOND, THIRD, FOUR> classitem,                   \
            FmtContext&                           ctx                          \
        ) const {                                                              \
            std::ostringstream out{std::string(classitem)};                    \
            return std::ranges::copy(std::move(out).str(), ctx.out()).out;     \
        }                                                                      \
    };

#define RAYGAME_MAKE_FORMAT_FROM_STRING(classname)                             \
    template<>                                                                 \
    struct std::formatter<classname, char> {                                   \
        template<typename ParseContext>                                        \
        constexpr ParseContext::iterator parse(ParseContext& ctx) {            \
            auto iter = ctx.begin();                                           \
            if (iter == ctx.end()) {                                           \
                return iter;                                                   \
            }                                                                  \
            if (iter != ctx.end() && *iter != '}') {                           \
                throw std::format_error("Invalid format args for classname."); \
            }                                                                  \
            return iter;                                                       \
        }                                                                      \
        template<class FmtContext>                                             \
        FmtContext::iterator                                                   \
        format(classname classitem, FmtContext& ctx) const {                   \
            std::ostringstream clsout{std::string(classitem)};                 \
            return std::ranges::copy(std::move(clsout).str(), ctx.out()).out;  \
        }                                                                      \
    };

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

using pos_t = RAYGAME_POSITION_TYPE;
static_assert(std::is_signed_v<pos_t>);

using dis_t = RAYGAME_DISTANCE_TYPE;
static_assert(std::is_unsigned_v<dis_t>);

template<typename first, typename second = first>
class Pair {
public:
    using A = first;
    using B = second;
    //NOLINTBEGIN(*-non-private-member-*)
    A a;
    B b;

    //NOLINTEND(*-non-private-member-*)

    constexpr explicit operator std::string() const {
        if constexpr (std::is_same_v<decltype(a), decltype(b)>) {
            return std::format(
                "Pair<{}>(a: {}, b: {})",
                core::debug::type_name(a),
                a,
                b
            );
        } else {
            return std::format(
                "Pair<{}, {}>(a: {}, b: {})",
                core::debug::type_name(a),
                core::debug::type_name(b),
                a,
                b
            );
        }
    }
};

RAYGAME_EXTERN_TEMPLATE_INTS(Pair);

template<typename first, typename second = first, typename third = second>
class Triple {
public:
    using A = first;
    using B = second;
    using C = third;
    //NOLINTBEGIN(*-non-private-member-*)
    A a;
    B b;
    C c;

    //NOLINTEND(*-non-private-member-*)

    constexpr explicit operator std::string() const {
        if constexpr (std::is_same_v<decltype(a), decltype(b)>
                      && std::is_same_v<decltype(a), decltype(c)>) {
            return std::format(
                "Triple<{}>(a: {}, b: {}, c: {})",
                core::debug::type_name(a),
                a,
                b,
                c
            );
        } else {
            return std::format(
                "Triple<{}, {}, {}>(a: {}, b: {}, c: {})",
                core::debug::type_name(a),
                core::debug::type_name(b),
                core::debug::type_name(c),
                a,
                b,
                c
            );
        }
    }
};

RAYGAME_EXTERN_TEMPLATE_INTS(Triple);

template<
    typename first,
    typename second = first,
    typename third  = second,
    typename fourth = third>
class Quad {
public:
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
    constexpr explicit operator std::string() const {
        if constexpr (std::is_same_v<decltype(a), decltype(b)>
                      && std::is_same_v<decltype(a), decltype(c)>
                      && std::is_same_v<decltype(a), decltype(d)>) {
            return std::format(
                "Quad<{}>(a: {}, b: {}, c: {}, d: {})",
                core::debug::type_name(a),
                a,
                b,
                c,
                d
            );
        } else {
            return std::format(
                "Quad<{}, {}, {}, {}>(a: {}, b: {}, c: {}, d: {})",
                core::debug::type_name(a),
                core::debug::type_name(b),
                core::debug::type_name(c),
                core::debug::type_name(d),
                a,
                b,
                c,
                d
            );
        }
    }
};

RAYGAME_EXTERN_TEMPLATE_INTS(Quad);

} // namespace core

RAYGAME_MAKE_FORMAT_TEMPLATE_2(core::Pair)
RAYGAME_MAKE_FORMAT_TEMPLATE_3(core::Triple)
RAYGAME_MAKE_FORMAT_TEMPLATE_4(core::Quad)
