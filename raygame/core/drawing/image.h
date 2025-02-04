#pragma once
#include "raygame/core/condition.h"
#include "raygame/core/drawing/pixel.h"
#include "raygame/core/math/rect.h"
#include "raygame/core/math/vector.h"
#include "raygame/core/matrix.h"
#include <mdspan>

namespace core::drawing {
//! Non-owning Image type
class Image {
    Rect<size_t>                                 m_rect;
    std::mdspan<Pixel, std::dextents<size_t, 2>> m_mdspan;

public:
    template<size_t N>
    constexpr explicit Image(
        const std::array<Pixel, N>& in_buf,
        Vec2<size_t>                size
    )
        : m_rect(size)
        , m_mdspan(in_buf.data(), size.x, size.y) {
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

    [[nodiscard]]
    constexpr Vec2<size_t> pos() const {
        return m_rect.pos();
    }

    [[nodiscard]]
    constexpr size_t x() const {
        return m_rect.x();
    }

    [[nodiscard]]
    constexpr size_t y() const {
        return m_rect.y();
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
};
} // namespace core::drawing
