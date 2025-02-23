#pragma once
#include "raygame/core/condition.h"
#include "raygame/core/drawing/pixel.h"
#include "raygame/core/math/rect.h"
#include "raygame/core/math/vector.h"
#include "raygame/core/matrix.h"
#include <mdspan>

namespace core::drawing {

namespace concepts {
template<typename T>
concept Drawable = requires(T drawable, T other) {
    other = drawable;
    other = std::move(drawable);
    drawable.get_item(0, 0);
    drawable.row(0);
    drawable.height();
    drawable.pos_x();
    drawable.pos_y();
    drawable.width();
};
} // namespace concepts

//! Non-owning Image type
template<size_t Width, size_t Height>
class Image {
    using img_extents = std::extents<size_t, Width, Height>;
    static constexpr size_t img_size =
        core::math::safe_mult<size_t>(Width, Height);

    Rect<size_t>                    m_rect;
    std::array<Pixel, img_size>     m_buffer;
    std::mdspan<Pixel, img_extents> m_mdspan;

public:
    constexpr explicit Image(std::array<Pixel, img_size>&& in_buf)
        : m_rect({Width, Height})
        , m_buffer(std::move(in_buf))
        , m_mdspan(m_buffer.data(), std::extents(Width, Height)) {}

    constexpr const Pixel&           get_item(size_t row, size_t col);
    constexpr std::span<const Pixel> row(size_t col);

    constexpr size_t width() { return m_rect.width(); }

    constexpr size_t height() { return m_rect.height(); }

    constexpr size_t pos_x() { return m_rect.pos_x(); }

    constexpr size_t pos_y() { return m_rect.pos_y(); }
};

static_assert(concepts::Drawable<Image<1, 1>>, "Image not Drawable");

class ImageView {
    Rect<size_t>                                       m_rect;
    std::mdspan<const Pixel, std::dextents<size_t, 2>> m_mdspan;

public:
    template<size_t N>
    constexpr explicit ImageView(
        const std::array<Pixel, N>& in_buf,
        Vec2<size_t>                size
    )
        : m_rect(size)
        , m_mdspan(in_buf.data(), std::extents(size.x, size.y)) {
        const auto mulsize = math::safe_mult<size_t>(size.x, size.y);
        condition::pre_condition(
            N == mulsize,
            std ::format(
                "Size mismatch between m_buffer ({}) and size ({})",
                N,
                mulsize
            )
        );
    }

    [[nodiscard]]
    constexpr std::span<const Pixel> row(size_t col) const {
        return {&m_mdspan[0, col], &m_mdspan[width() - 1, col]};
    }

    constexpr void move(size_t posx, size_t posy) { m_rect.pos(posx, posy); }

    [[nodiscard]]
    constexpr Vec2<size_t> pos() const {
        return m_rect.pos();
    }

    [[nodiscard]]
    constexpr size_t pos_x() const {
        return m_rect.pos_x();
    }

    [[nodiscard]]
    constexpr size_t pos_y() const {
        return m_rect.pos_y();
    }

    [[nodiscard]]
    constexpr size_t height() const {
        return m_rect.height();
    }

    [[nodiscard]]
    constexpr size_t width() const {
        return m_rect.width();
    }

    [[nodiscard]]
    constexpr size_t size() const {
        return m_mdspan.size();
    }

    [[nodiscard]]
    constexpr const Pixel& get_item(size_t row, size_t col) const {
        return m_mdspan[row, col];
    }

    [[nodiscard]]
    constexpr auto operator[](size_t row, size_t col) const {
        return m_mdspan[row, col];
    }

    [[nodiscard]]
    constexpr auto extent(size_t ext) const {
        return m_mdspan.extent(ext);
    }

    [[nodiscard]]
    constexpr auto data() const {
        return m_mdspan.data_handle();
    }
};

static_assert(concepts::Drawable<ImageView>, "ImageView not Drawable");
} // namespace core::drawing
