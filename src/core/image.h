#pragma once
#include "core/base/types.h"
#include "core/pixel.h"
#include <vector>

namespace core {

class Image {
private:
    std::vector<Pixel> m_image_data;
    int32_t            m_width;
    int32_t            m_height;

public:
    explicit Image(auto& embed);
    ~Image();
    Image(const Image&)            = default;
    Image(Image&&)                 = default;
    Image& operator=(const Image&) = default;
    Image& operator=(Image&&)      = default;

    inline constexpr Pixel* data() {
        return m_image_data.data();
    }

    [[nodiscard]]
    inline constexpr int32_t width() const {
        return m_width;
    }

    [[nodiscard]]
    inline constexpr int32_t height() const {
        return m_height;
    }
};

} // namespace core
