#pragma once
#include "core/types.h"
#include <vector>

namespace core {

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

class Image {
private:
    std::vector<Pixel> m_image_data;
    int32_t            m_width;
    int32_t            m_height;
    int32_t            m_n_mipmaps;

public:
    Image(auto embed);
    ~Image();
    Image(const Image&)            = default;
    Image(Image&&)                 = default;
    Image& operator=(const Image&) = default;
    Image& operator=(Image&&)      = default;

    inline Pixel* data() {
        return m_image_data.data();
    }

    inline int32_t width() {
        return m_width;
    }

    inline int32_t height() {
        return m_height;
    }

    inline int32_t n_mipmaps() {
        return m_n_mipmaps;
    }
};

} // namespace core
