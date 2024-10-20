#pragma once

#include "core/math/arithmetic.h"
#include "core/math/math.h"
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

    void set_pos(Vec2<Pos_t> vec) {
        x = vec.x;
        y = vec.y;
    }

    void set_size(Vec2<Pos_t> vec) {
        width  = vec.x;
        height = vec.y;
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    void translate(Vec2<Pos_t> vec) {
        x = core::math::safe_add<Pos_t, MR>(x, vec.x);
        y = core::math::safe_add<Pos_t, MR>(y, vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    void scale_add(Vec2<Dis_t> vec) {
        width  = core::math::safe_add<Dis_t, MR>(x, vec.x);
        height = core::math::safe_add<Dis_t, MR>(y, vec.y);
    }

    template<math::MathRule MR = math::MR_DEFAULT>
    void scale_mult(Vec2<Dis_t> vec) {
        width  = core::math::safe_mult<Dis_t, MR>(x, vec.x);
        height = core::math::safe_mult<Dis_t, MR>(y, vec.y);
    }

    constexpr inline operator std::string() {
        return "Rect(x: " + std::to_string(x) + ", y: " + std::to_string(y)
               + ", width: " + std::to_string(width)
               + ", height: " + std::to_string(height) + ")";
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
