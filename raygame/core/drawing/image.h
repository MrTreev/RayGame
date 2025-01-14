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
    Rect<size_t> m_rect;

    ViewMatrix<Pixel> m_matrix;

public:
    template<size_t img_size>
    constexpr explicit Image(
        const std::array<const Pixel, img_size>& in_buf,
        Vec2<size_t>                             size
    )
        : m_rect(size)
        , m_matrix(in_buf.data(), size.x, size.y) {
        condition::pre_condition(
            img_size == math::safe_mult<size_t>(size.x, size.y),
            "Size mismatch between m_buffer and size"
        );
    }

    [[nodiscard]]
    constexpr std::span<const Pixel> row(size_t col) const {
        return {&m_matrix[0, col], &m_matrix[width() - 1, col]};
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
        return m_matrix.size();
    }

    [[nodiscard]]
    const Pixel& get_item(size_t row, size_t col) const {
        return m_matrix[row, col];
    }
};
} // namespace core::drawing
