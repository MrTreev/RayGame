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
    Pos_t x{};
    Pos_t y{};
    Dis_t width{};
    Dis_t height{};

public:
    constexpr Rect() = default;

    constexpr Rect(Vec2<Pos_t> pos_vec, Vec2<Dis_t> dist_vec)
        : x(pos_vec.x)
        , y(pos_vec.y)
        , width(dist_vec.x)
        , height(dist_vec.y) {}

    constexpr void zero() {
        x      = 0;
        y      = 0;
        width  = 0;
        height = 0;
    }

    [[nodiscard]]
    constexpr Vec2<Pos_t> pos() const {
        return {x, y};
    }

    [[nodiscard]]
    constexpr Vec2<Dis_t> size() const {
        return {width, height};
    }

    constexpr explicit operator std::string() const {
        return "Rect(x: " + std::to_string(x) + ", y: " + std::to_string(y)
               + ", width: " + std::to_string(width)
               + ", height: " + std::to_string(height) + ")";
    }

    template<typename P, typename D>
    constexpr bool operator==(const Rect<P, D>& other) const {
        return (
            std::cmp_equal(x, other.x) && std::cmp_equal(y, other.y)
            && std::cmp_equal(width, other.width)
            && std::cmp_equal(height, other.height)
        );
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void pos(auto setx, auto sety) {
        x = core::math::numeric_cast<Pos_t, MR>(setx);
        y = core::math::numeric_cast<Pos_t, MR>(sety);
    }

    template<typename P, math::MathRule MR = math::MR_DEFAULT>
    constexpr void pos(Vec2<P> vec) {
        x = core::math::numeric_cast<Pos_t, MR>(vec.x);
        y = core::math::numeric_cast<Pos_t, MR>(vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void size(auto set_width, auto set_height) {
        width  = core::math::numeric_cast<Dis_t, MR>(set_width);
        height = core::math::numeric_cast<Dis_t, MR>(set_height);
    }

    template<typename P, math::MathRule MR = math::MR_DEFAULT>
    constexpr void size(Vec2<P> vec) {
        width  = core::math::numeric_cast<Dis_t, MR>(vec.x);
        height = core::math::numeric_cast<Dis_t, MR>(vec.y);
    }

    template<typename P, math::MathRule MR = math::MR_DEFAULT>
    constexpr void translate(Vec2<P> vec) {
        x = core::math::safe_add<Pos_t, MR>(x, vec.x);
        y = core::math::safe_add<Pos_t, MR>(y, vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void translate(auto translate_x, auto translate_y) {
        x = core::math::safe_add<Pos_t, MR>(x, translate_x);
        y = core::math::safe_add<Pos_t, MR>(y, translate_y);
    }

    template<typename D, math::MathRule MR = math::MR_DEFAULT>
    constexpr void scale_add(Vec2<D> vec) {
        width  = core::math::safe_add<Dis_t, MR>(width, vec.x);
        height = core::math::safe_add<Dis_t, MR>(height, vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void scale_add(auto width_add, auto height_add) {
        width  = core::math::safe_add<Dis_t, MR>(width, width_add);
        height = core::math::safe_add<Dis_t, MR>(height, height_add);
    }

    template<typename D, math::MathRule MR = math::MR_DEFAULT>
    constexpr void scale_mult(Vec2<D> vec) {
        width  = core::math::safe_mult<Dis_t, MR>(width, vec.x);
        height = core::math::safe_mult<Dis_t, MR>(height, vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void scale_mult(auto width_mult, auto height_mult) {
        width  = core::math::safe_mult<Dis_t, MR>(width, width_mult);
        height = core::math::safe_mult<Dis_t, MR>(height, height_mult);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    constexpr void scale_mult(auto mult) {
        width  = core::math::safe_mult<Dis_t, MR>(width, mult);
        height = core::math::safe_mult<Dis_t, MR>(height, mult);
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
