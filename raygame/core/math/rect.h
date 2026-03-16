#pragma once

#include "raygame/core/math/arithmetic.h"
#include "raygame/core/math/vector.h"
#include "raygame/core/types.h"
#include <string>

namespace core {

template<typename DistanceType>
class Rect {
public:
    using Dis_t = DistanceType;

private:
    Dis_t m_width{};
    Dis_t m_height{};

public:
    constexpr Rect() = default;

    constexpr explicit Rect(Vec2<Dis_t> dist_vec)
        : m_width(dist_vec.m_x)
        , m_height(dist_vec.m_y) {}

    constexpr void zero() {
        m_width  = 0;
        m_height = 0;
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
        return std::format("Rect(width: {}, height: {})", m_width, m_height);
    }

    template<typename D>
    constexpr bool operator==(const Rect<D>& other) const {
        return (std::cmp_equal(m_width, other.m_width) && std::cmp_equal(m_height, other.m_height));
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void size(auto set_width, auto set_height) {
        m_width  = core::math::numeric_cast<Dis_t, MR>(set_width);
        m_height = core::math::numeric_cast<Dis_t, MR>(set_height);
    }

    template<typename D, math::MathRule MR = math::MR_DEFAULT>
    constexpr void size(Vec2<D> vec) {
        m_width  = core::math::numeric_cast<Dis_t, MR>(vec.m_x);
        m_height = core::math::numeric_cast<Dis_t, MR>(vec.m_y);
    }

    template<typename D, math::MathRule MR = math::MR_DEFAULT>
    constexpr void scale_add(Vec2<D> vec) {
        m_width  = core::math::safe_add<Dis_t, MR>(m_width, vec.m_x);
        m_height = core::math::safe_add<Dis_t, MR>(m_height, vec.m_y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void scale_add(auto width_add, auto height_add) {
        m_width  = core::math::safe_add<Dis_t, MR>(m_width, width_add);
        m_height = core::math::safe_add<Dis_t, MR>(m_height, height_add);
    }

    template<typename D, math::MathRule MR = math::MR_DEFAULT>
    constexpr void scale_mult(Vec2<D> vec) {
        m_width  = core::math::safe_mult<Dis_t, MR>(m_width, vec.m_x);
        m_height = core::math::safe_mult<Dis_t, MR>(m_height, vec.m_y);
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
