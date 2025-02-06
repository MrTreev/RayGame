#include "raygame/core/types.h"
#include <mdspan>

namespace core {

template<typename T, auto Width, auto Height>
class Matrix {
    std::array<T, (Width * Height)>                     m_buffer;
    std::mdspan<T, std::extents<size_t, Width, Height>> m_mdspan;

public:
    [[nodiscard]]
    constexpr size_t height() const {
        return Height;
    }

    [[nodiscard]]
    constexpr size_t width() const {
        return Width;
    }

    explicit Matrix(auto... args)
        : m_buffer({std::forward<decltype(args)>(args)...})
        , m_mdspan(m_buffer.data(), Width, Height) {
        static_assert(Width > 0);
        static_assert(Height > 0);
    }

    const auto& operator[](const size_t& xpos, const size_t& ypos) const {
        return m_mdspan[ypos, xpos];
    }

    auto& operator[](const size_t& xpos, const size_t& ypos) {
        return m_mdspan[ypos, xpos];
    }
};

template<typename T>
class ViewMatrix {
    std::mdspan<T, std::dextents<size_t, 2>> m_mdspan;

public:
    explicit ViewMatrix(const auto&& container, size_t width_, size_t height_)
        : m_mdspan(container, width_, height_) {}

    const T& operator[](const size_t& xpos, const size_t& ypos) const {
        return m_mdspan[ypos, xpos];
    }

    T& operator[](const size_t& xpos, const size_t& ypos) {
        return m_mdspan[ypos, xpos];
    }

    [[nodiscard]]
    constexpr size_t height() const {
        return m_mdspan.extent(0);
    }

    [[nodiscard]]
    constexpr size_t width() const {
        return m_mdspan.extent(1);
    }

    [[nodiscard]]
    constexpr size_t size() const {
        return (width() * height());
    }
};

} // namespace core
