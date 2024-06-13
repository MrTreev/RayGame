#pragma once
#include "core/types.h"
#include <string>
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
    std::vector<Pixel> _image_data;
    int32_t            _width;
    int32_t            _height;
    int32_t            _n_mipmaps;

public:
    explicit Image(const std::string& filepath);
    explicit Image(std::string_view filepath);

    Image(const Image&)            = default;
    Image(Image&&)                 = default;
    Image& operator=(const Image&) = default;
    Image& operator=(Image&&)      = default;
    ~Image()                       = default;

    inline Pixel* data() {
        return _image_data.data();
    }

    inline int32_t width() {
        return _width;
    }

    inline int32_t height() {
        return _height;
    }

    inline int32_t n_mipmaps() {
        return _n_mipmaps;
    }
};

} // namespace core
