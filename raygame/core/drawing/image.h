#pragma once
#include "raygame/core/condition.h"
#include "raygame/core/drawing/pixel.h"
#include "raygame/core/math/rect.h"
#include "raygame/core/math/vector.h"
#include <format>
#include <mdspan>
#include <span>

namespace core::drawing {
//! Non-owning Image type
class Image {
    Rect<size_t>           m_rect;
    std::span<const Pixel> m_buffer;

    [[nodiscard]]
    constexpr size_t idx(size_t row, size_t col) const {
        condition::pre_condition(
            row < height(),
            std::format("row {} out of bounds, max: {}", row, height())
        );
        condition::pre_condition(
            col < width(),
            std::format("col {} out of bounds, max: {}", col, width())
        );
        return (row * width()) + col;
    }

public:
    template<size_t img_size>
    constexpr explicit Image(
        [[maybe_unused]]
        const std::array<const Pixel, img_size>& in_buf,
        Vec2<size_t>                             size
    )
        : m_rect(size)
        , m_buffer(in_buf) {
        condition::pre_condition(
            img_size == math::safe_mult<size_t>(size.x, size.y),
            "Size mismatch between m_buffer and size"
        );
    }

    template<size_t img_size>
    constexpr explicit Image(
        [[maybe_unused]]
        const std::array<const uint8_t, img_size>& in_buf,
        Vec2<size_t>                               size
    )
        : Image(
              // NOLINTNEXTLINE(*-reinterpret-cast)
              reinterpret_cast<const std::array<const Pixel, img_size / 4>&>(
                  in_buf
              ),
              size
          ) {}

    [[nodiscard]]
    constexpr std::span<const Pixel> row(size_t col) const {
        return {&m_buffer[idx(0, col)], &m_buffer[idx(width() - 1, col)]};
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
        return m_buffer.size();
    }

    [[nodiscard]]
    const Pixel& get_item(size_t row, size_t col) const {
        return m_buffer[idx(row, col)];
    }
};
} // namespace core::drawing
