#pragma once

#include "raygame/core/math/arithmetic.h"
#include "raygame/core/math/vector.h"
#include <string>

namespace core {

template<typename PositionType, typename DistanceType = PositionType>
class Rect {
public:
    using Pos_t = PositionType;
    using Dis_t = DistanceType;

private:
    Dis_t m_width{};
    Dis_t m_height{};
    Pos_t m_x{};
    Pos_t m_y{};

public:
    constexpr Rect() = default;

    constexpr explicit Rect(Vec2<Dis_t> dist_vec)
        : m_width(dist_vec.x)
        , m_height(dist_vec.y)
        , m_x(0)
        , m_y(0) {}

    constexpr Rect(Vec2<Pos_t> pos_vec, Vec2<Dis_t> dist_vec)
        : m_width(dist_vec.x)
        , m_height(dist_vec.y)
        , m_x(pos_vec.x)
        , m_y(pos_vec.y) {}

    constexpr void zero() {
        m_x      = 0;
        m_y      = 0;
        m_width  = 0;
        m_height = 0;
    }

    [[nodiscard]]
    constexpr Vec2<Pos_t> pos() const {
        return {m_x, m_y};
    }

    [[nodiscard]]
    constexpr Vec2<Dis_t> size() const {
        return {m_width, m_height};
    }

    [[nodiscard]]
    constexpr Dis_t width() const {
        return m_width;
    }

    [[nodiscard]]
    constexpr Dis_t height() const {
        return m_height;
    }

    constexpr explicit operator std::string() const {
        return "Rect(x: " + std::to_string(m_x) + ", y: " + std::to_string(m_y)
               + ", width: " + std::to_string(m_width)
               + ", height: " + std::to_string(m_height) + ")";
    }

    template<typename P, typename D>
    constexpr bool operator==(const Rect<P, D>& other) const {
        return (
            std::cmp_equal(m_x, other.m_x) && std::cmp_equal(m_y, other.m_y)
            && std::cmp_equal(m_width, other.m_width)
            && std::cmp_equal(m_height, other.m_height)
        );
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void pos(auto setx, auto sety) {
        m_x = core::math::numeric_cast<Pos_t, MR>(setx);
        m_y = core::math::numeric_cast<Pos_t, MR>(sety);
    }

    template<typename P, math::MathRule MR = math::MR_DEFAULT>
    constexpr void pos(Vec2<P> vec) {
        m_x = core::math::numeric_cast<Pos_t, MR>(vec.x);
        m_y = core::math::numeric_cast<Pos_t, MR>(vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void size(auto set_width, auto set_height) {
        m_width  = core::math::numeric_cast<Dis_t, MR>(set_width);
        m_height = core::math::numeric_cast<Dis_t, MR>(set_height);
    }

    template<typename P, math::MathRule MR = math::MR_DEFAULT>
    constexpr void size(Vec2<P> vec) {
        m_width  = core::math::numeric_cast<Dis_t, MR>(vec.x);
        m_height = core::math::numeric_cast<Dis_t, MR>(vec.y);
    }

    template<typename P, math::MathRule MR = math::MR_DEFAULT>
    constexpr void translate(Vec2<P> vec) {
        m_x = core::math::safe_add<Pos_t, MR>(m_x, vec.x);
        m_y = core::math::safe_add<Pos_t, MR>(m_y, vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void translate(auto translate_x, auto translate_y) {
        m_x = core::math::safe_add<Pos_t, MR>(m_x, translate_x);
        m_y = core::math::safe_add<Pos_t, MR>(m_y, translate_y);
    }

    template<typename D, math::MathRule MR = math::MR_DEFAULT>
    constexpr void scale_add(Vec2<D> vec) {
        m_width  = core::math::safe_add<Dis_t, MR>(m_width, vec.x);
        m_height = core::math::safe_add<Dis_t, MR>(m_height, vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void scale_add(auto width_add, auto height_add) {
        m_width  = core::math::safe_add<Dis_t, MR>(m_width, width_add);
        m_height = core::math::safe_add<Dis_t, MR>(m_height, height_add);
    }

    template<typename D, math::MathRule MR = math::MR_DEFAULT>
    constexpr void scale_mult(Vec2<D> vec) {
        m_width  = core::math::safe_mult<Dis_t, MR>(m_width, vec.x);
        m_height = core::math::safe_mult<Dis_t, MR>(m_height, vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void scale_mult(auto width_mult, auto height_mult) {
        m_width  = core::math::safe_mult<Dis_t, MR>(m_width, width_mult);
        m_height = core::math::safe_mult<Dis_t, MR>(m_height, height_mult);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void scale_mult(auto mult) {
        m_width  = core::math::safe_mult<Dis_t, MR>(m_width, mult);
        m_height = core::math::safe_mult<Dis_t, MR>(m_height, mult);
    }
};

extern template class Rect<uint8_t>;
extern template class Rect<uint16_t>;
extern template class Rect<uint32_t>;
extern template class Rect<uint64_t>;
extern template class Rect<int8_t>;
extern template class Rect<int16_t>;
extern template class Rect<int32_t>;
extern template class Rect<int64_t>;

} // namespace core
