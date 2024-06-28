#pragma once
#include "core/types.h"
#include <vector>

namespace core {

struct Pixel {
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
    uint8_t m_alpha;
};

class Image {
private:
    std::vector<Pixel> m_image_data;
    int32_t            m_width;
    int32_t            m_height;
    int32_t            m_n_mipmaps;

public:
    explicit Image(auto embed);
    ~Image();
    Image(const Image&)            = default;
    Image(Image&&)                 = default;
    Image& operator=(const Image&) = default;
    Image& operator=(Image&&)      = default;

    inline Pixel* data() {
        return m_image_data.data();
    }

    [[nodiscard]]
    inline int32_t width() const {
        return m_width;
    }

    [[nodiscard]]
    inline int32_t height() const {
        return m_height;
    }

    [[nodiscard]]
    inline int32_t n_mipmaps() const {
        return m_n_mipmaps;
    }
};

} // namespace core
