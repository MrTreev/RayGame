#pragma once
#include "raygame/core/config.h"
#include "raygame/core/debug.h"
#include <cstdint>
#include <format>
#include <sstream>

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

template<typename t_first_t, typename t_second_t = t_first_t>
class Pair {
private:
    t_first_t  m_first;
    t_second_t m_second;

public:
    using first_t  = t_first_t;
    using second_t = t_second_t;

    Pair(first_t first, second_t second)
        : m_first(first)
        , m_second(second) {}

    first_t first() const { return m_first; }

    second_t second() const { return m_second; }

    constexpr explicit operator std::string() const {
        if constexpr (std::is_same_v<decltype(m_first), decltype(m_second)>) {
            return std::format(
                "Pair<{}>(a: {}, b: {})",
                core::debug::type_name(m_first),
                m_first,
                m_second
            );
        } else {
            return std::format(
                "Pair<{}, {}>(a: {}, b: {})",
                core::debug::type_name(m_first),
                core::debug::type_name(m_second),
                m_first,
                m_second
            );
        }
    }

    RAYGAME_ADD_STRUCTURED_BINDINGS_2(m_first, m_second)
};

template<typename t_first_t, typename t_second_t = t_first_t, typename t_third_t = t_second_t>
class Triple {
private:
    t_first_t  m_first;
    t_second_t m_second;
    t_third_t  m_third;

public:
    using first_t  = t_first_t;
    using second_t = t_second_t;
    using third_t  = t_third_t;

    Triple(first_t first, second_t second, third_t third)
        : m_first(first)
        , m_second(second)
        , m_third(third) {}

    first_t first() const { return m_first; }

    second_t second() const { return m_second; }

    third_t third() const { return m_third; }

    constexpr explicit operator std::string() const {
        if constexpr (std::is_same_v<decltype(m_first), decltype(m_second)>
                      && std::is_same_v<decltype(m_first), decltype(m_third)>) {
            return std::format(
                "Triple<{}>(a: {}, b: {}, c: {})",
                core::debug::type_name(m_first),
                m_first,
                m_second,
                m_third
            );
        } else {
            return std::format(
                "Triple<{}, {}, {}>(a: {}, b: {}, c: {})",
                core::debug::type_name(m_first),
                core::debug::type_name(m_second),
                core::debug::type_name(m_third),
                m_first,
                m_second,
                m_third
            );
        }
    }

    RAYGAME_ADD_STRUCTURED_BINDINGS_3(m_first, m_second, m_third)
};

template<
    typename t_first_t,
    typename t_second_t = t_first_t,
    typename t_third_t  = t_second_t,
    typename t_fourth_t = t_third_t>
class Quad {
    t_first_t  m_first;
    t_second_t m_second;
    t_third_t  m_third;
    t_fourth_t m_fourth;

public:
    using first_t  = t_first_t;
    using second_t = t_second_t;
    using third_t  = t_third_t;
    using fourth_t = t_fourth_t;

    Quad(first_t first, second_t second, third_t third, fourth_t fourth)
        : m_first(first)
        , m_second(second)
        , m_third(third)
        , m_fourth(fourth) {}

    first_t first() const { return m_first; }

    second_t second() const { return m_second; }

    third_t third() const { return m_third; }

    third_t fourth() const { return m_fourth; }

    auto operator<=>(const Quad&) const = default;

    constexpr explicit operator std::string() const {
        if constexpr (std::is_same_v<decltype(m_first), decltype(m_second)>
                      && std::is_same_v<decltype(m_first), decltype(m_third)>
                      && std::is_same_v<decltype(m_first), decltype(m_fourth)>) {
            return std::format(
                "Quad<{}>(a: {}, b: {}, c: {}, d: {})",
                core::debug::type_name(m_first),
                m_first,
                m_second,
                m_third,
                m_fourth
            );
        } else {
            return std::format(
                "Quad<{}, {}, {}, {}>(a: {}, b: {}, c: {}, d: {})",
                core::debug::type_name(m_first),
                core::debug::type_name(m_second),
                core::debug::type_name(m_third),
                core::debug::type_name(m_fourth),
                m_first,
                m_second,
                m_third,
                m_fourth
            );
        }
    }

    RAYGAME_ADD_STRUCTURED_BINDINGS_4(m_first, m_second, m_third, m_fourth)
};
} // namespace core

// clang-format off
// Parentheses would be incorrect here
// NOLINTBEGIN(*-macro-usage,bugprone-macro-parentheses)
#define RAYGAME_MAKE_FORMAT_TEMPLATE_1(classname) template<typename TNAME> struct std::formatter<classname<TNAME>, char> { template<typename ParseContext> constexpr ParseContext::iterator parse(ParseContext& ctx) { auto iter = ctx.begin(); if (iter == ctx.end()) { return iter; } if (iter != ctx.end() && *iter != '}') { throw std::format_error("Invalid format args for classname."); } return iter; } template<class FmtContext> FmtContext::iterator format(classname<TNAME> classitem, FmtContext& ctx) const { std::ostringstream out{std::string(classitem)}; return std::ranges::copy(std::move(out).str(), ctx.out()).out; } }
#define RAYGAME_MAKE_FORMAT_TEMPLATE_2(classname) template<typename FIRST, typename SECOND> struct std::formatter<classname<FIRST, SECOND>, char> { template<typename ParseContext> constexpr ParseContext::iterator parse(ParseContext& ctx) { auto iter = ctx.begin(); if (iter == ctx.end()) { return iter; } if (iter != ctx.end() && *iter != '}') { throw std::format_error("Invalid format args for classname."); } return iter; } template<class FmtContext> FmtContext::iterator format(classname<FIRST, SECOND> classitem, FmtContext& ctx) const { std::ostringstream out{std::string(classitem)}; return std::ranges::copy(std::move(out).str(), ctx.out()).out; } }
#define RAYGAME_MAKE_FORMAT_TEMPLATE_3(classname) template<typename FIRST, typename SECOND, typename THIRD> struct std::formatter<classname<FIRST, SECOND, THIRD>, char> { template<typename ParseContext> constexpr ParseContext::iterator parse(ParseContext& ctx) { auto iter = ctx.begin(); if (iter == ctx.end()) { return iter; } if (iter != ctx.end() && *iter != '}') { throw std::format_error("Invalid format args for classname."); } return iter; } template<class FmtContext> FmtContext::iterator format( classname<FIRST, SECOND, THIRD> classitem, FmtContext& ctx ) const { std::ostringstream out{std::string(classitem)}; return std::ranges::copy(std::move(out).str(), ctx.out()).out; } }
#define RAYGAME_MAKE_FORMAT_TEMPLATE_4(classname) template<typename FIRST, typename SECOND, typename THIRD, typename FOUR> struct std::formatter<classname<FIRST, SECOND, THIRD, FOUR>, char> { template<typename ParseContext> constexpr ParseContext::iterator parse(ParseContext& ctx) { auto iter = ctx.begin(); if (iter == ctx.end()) { return iter; } if (iter != ctx.end() && *iter != '}') { throw std::format_error("Invalid format args for classname."); } return iter; } template<class FmtContext> FmtContext::iterator format( classname<FIRST, SECOND, THIRD, FOUR> classitem, FmtContext& ctx ) const { std::ostringstream out{std::string(classitem)}; return std::ranges::copy(std::move(out).str(), ctx.out()).out; } }
#define RAYGAME_MAKE_FORMAT_FROM_STRING(classname) template<> struct std::formatter<classname, char> { template<typename ParseContext> constexpr ParseContext::iterator parse(ParseContext& ctx) { auto iter = ctx.begin(); if (iter == ctx.end()){return iter; } if (iter != ctx.end() && *iter != '}') { throw std::format_error("Invalid format args for classname."); } return iter; } template<class FmtContext> FmtContext::iterator format(classname classitem, FmtContext& ctx) const { std::ostringstream clsout{std::string(classitem)}; return std::ranges::copy(std::move(clsout).str(), ctx.out()).out; } }
// NOLINTEND(*-macro-usage,bugprone-macro-parentheses)
// clang-format on

RAYGAME_MAKE_FORMAT_TEMPLATE_2(core::Pair);
RAYGAME_ADD_TUPLE_INTERFACE(core::Pair, 2);

RAYGAME_MAKE_FORMAT_TEMPLATE_3(core::Triple);
RAYGAME_ADD_TUPLE_INTERFACE(core::Triple, 3);

RAYGAME_MAKE_FORMAT_TEMPLATE_4(core::Quad);
RAYGAME_ADD_TUPLE_INTERFACE(core::Quad, 4);
