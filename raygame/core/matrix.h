#include "raygame/core/types.h"
#include <initializer_list>
#include <mdspan>

namespace core {

template<typename T>
class MatrixBase {};

template<typename T, size_t Width, size_t Height>
class Matrix {
    std::array<T, (Width * Height) + 1>                 m_buffer;
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

    Matrix(std::initializer_list<T> args)
        : m_buffer(args)
        , m_mdspan(m_buffer.data(), Width, Height) {
        static_assert(Width > 0);
        static_assert(Height > 0);
    }

    const auto& operator[](const size_t& width, const size_t& height) {
        return m_mdspan[width, height];
    }
};

template<typename T, size_t Width, size_t Height>
class ViewMatrix {};

} // namespace core
