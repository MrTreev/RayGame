#pragma once

#include "core/math/arithmetic.h"
#include "core/math/vector.h"
#include <string>

namespace core {

template<typename Pos_t, typename Dis_t = Pos_t>
class Rect {
public:
    using PositionType = Pos_t;
    using DistanceType = Dis_t;
    PositionType x;
    PositionType y;
    DistanceType width;
    DistanceType height;

    constexpr Rect() = default;

    constexpr Rect(Pos_t x_, Pos_t y_, Dis_t width_, Dis_t height_)
        : x(x_)
        , y(y_)
        , width(width_)
        , height(height_) {}

    constexpr Rect(Vec2<Pos_t> pos_vec, Vec2<Dis_t> dist_vec)
        : x(pos_vec.x)
        , y(pos_vec.y)
        , width(dist_vec.x)
        , height(dist_vec.y) {}

    void zero() {
        x      = 0;
        y      = 0;
        width  = 0;
        height = 0;
    }

    void set(auto set_x, auto set_y, auto set_width, auto set_height) {
        x      = set_x;
        y      = set_y;
        width  = set_width;
        height = set_height;
    }

    constexpr Vec2<Pos_t> pos() {
        return {x, y};
    }

    constexpr Vec2<Dis_t> size() {
        return {width, height};
    }

    constexpr operator std::string() const {
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
    void pos(auto setx, auto sety) {
        x = core::math::numeric_cast<Pos_t, MR>(setx);
        y = core::math::numeric_cast<Pos_t, MR>(sety);
    }

    template<typename P, math::MathRule MR = math::MR_DEFAULT>
    void pos(Vec2<P> vec) {
        x = core::math::numeric_cast<Pos_t, MR>(vec.x);
        y = core::math::numeric_cast<Pos_t, MR>(vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    void size(auto set_width, auto set_height) {
        width  = core::math::numeric_cast<Dis_t, MR>(set_width);
        height = core::math::numeric_cast<Dis_t, MR>(set_height);
    }

    template<typename P, math::MathRule MR = math::MR_DEFAULT>
    void size(Vec2<P> vec) {
        width  = core::math::numeric_cast<Dis_t, MR>(vec.x);
        height = core::math::numeric_cast<Dis_t, MR>(vec.y);
    }

    template<typename P, math::MathRule MR = math::MR_DEFAULT>
    void translate(Vec2<P> vec) {
        x = core::math::safe_add<Pos_t, MR>(x, vec.x);
        y = core::math::safe_add<Pos_t, MR>(y, vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    void translate(auto translate_x, auto translate_y) {
        x = core::math::safe_add<Pos_t, MR>(x, translate_x);
        y = core::math::safe_add<Pos_t, MR>(y, translate_y);
    }

    template<typename D, math::MathRule MR = math::MR_DEFAULT>
    void scale_add(Vec2<D> vec) {
        width  = core::math::safe_add<Dis_t, MR>(width, vec.x);
        height = core::math::safe_add<Dis_t, MR>(height, vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    void scale_add(auto width_add, auto height_add) {
        width  = core::math::safe_add<Dis_t, MR>(width, width_add);
        height = core::math::safe_add<Dis_t, MR>(height, height_add);
    }

    template<typename D, math::MathRule MR = math::MR_DEFAULT>
    void scale_mult(Vec2<D> vec) {
        width  = core::math::safe_mult<Dis_t, MR>(width, vec.x);
        height = core::math::safe_mult<Dis_t, MR>(height, vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    void scale_mult(auto width_mult, auto height_mult) {
        width  = core::math::safe_mult<Dis_t, MR>(width, width_mult);
        height = core::math::safe_mult<Dis_t, MR>(height, height_mult);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    void scale_mult(auto mult) {
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
