#pragma once
#include "raygame/core/condition.h"
#include "raygame/core/drawing/pixel.h"
#include "raygame/core/math/rect.h"
#include "raygame/core/math/vector.h"
#include "raygame/core/matrix.h"
#include <mdspan>

namespace core::drawing {

class ImageView: private Rect<pos_t, dis_t> {
    std::mdspan<const Pixel, std::dextents<dis_t, 2>, std::layout_right> m_mdspan;
    using ImgRect = Rect<pos_t, dis_t>;

public:
    template<size_t N>
    constexpr explicit ImageView(const std::array<Pixel, N>& in_buf, Vec2<dis_t> size)
        : ImgRect(size)
        , m_mdspan(in_buf.data(), std::extents(size.x, size.y)) {
        const auto mulsize = math::safe_mult<dis_t>(size.x, size.y);
        condition::pre_condition(
            N == mulsize,
            std ::format("Size mismatch between m_buffer ({}) and size ({})", N, mulsize)
        );
    }

    constexpr void move(pos_t posx, pos_t posy) { pos(posx, posy); }

    using ImgRect::pos;
    using ImgRect::pos_x;
    using ImgRect::pos_y;

    using ImgRect::height;
    using ImgRect::width;

    using ImgRect::bottom;
    using ImgRect::top;

    using ImgRect::left;
    using ImgRect::right;

    [[nodiscard]]
    constexpr auto data() const {
        return m_mdspan.data_handle();
    }

    [[nodiscard]]
    constexpr dis_t size() const {
        return m_mdspan.size();
    }

    [[nodiscard]]
    constexpr const Pixel& at(dis_t row, dis_t col) const {
        condition::pre_condition(row <= height(), std::format("{} <= {}", row, height()));
        condition::pre_condition(col <= width(), std::format("{} <= {}", col, height()));
        return m_mdspan[row, col];
    }

    [[nodiscard]]
    constexpr const Pixel& get_item(dis_t row, dis_t col) const {
        return m_mdspan[row, col];
    }

    [[nodiscard]]
    constexpr auto operator[](dis_t row, dis_t col) const {
        return m_mdspan[row, col];
    }

    [[nodiscard]]
    constexpr auto extent(dis_t ext) const {
        return m_mdspan.extent(ext);
    }
};

template<dis_t Width, dis_t Height>
class Image: public ImageView {
    static constexpr size_t     img_size = core::math::safe_mult<size_t>(Width, Height);
    std::array<Pixel, img_size> m_buffer;

public:
    constexpr explicit Image(std::array<Pixel, img_size> in_buf)
        : m_buffer(std::move(in_buf))
        , ImageView(m_buffer, {Width, Height}) {}

    constexpr explicit Image(const std::array<Pixel, img_size>& in_buf)
        : m_buffer(in_buf)
        , ImageView(m_buffer, {Width, Height}) {}

    constexpr explicit Image(std::array<Pixel, img_size>&& in_buf)
        : m_buffer(std::move(in_buf))
        , ImageView(m_buffer, {Width, Height}) {}
};

} // namespace core::drawing
