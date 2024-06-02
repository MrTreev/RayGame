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
    size_t             _width;
    size_t             _height;

public:
    explicit Image(const std::string& filepath);
    explicit Image(std::string_view filepath);

    Image(const Image&)            = default;
    Image(Image&&)                 = default;
    Image& operator=(const Image&) = default;
    Image& operator=(Image&&)      = default;
    ~Image();
};

} // namespace core
