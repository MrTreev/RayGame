#include "core/image.h" // IWYU pragma: keep
#include "core/gui/backend.h"
#include <vector>

core::Image::Image(const std::string& filepath) {}

std::vector<core::Pixel> core::Image::load(void* data, const size_t& length) {
    std::vector<core::Pixel> image_data;
    image_data.reserve(length);
    auto* new_data = static_cast<char*>(data);
    for (size_t i = 0; i < length; i++) {
        image_data.emplace_back(new_data[i]);
    }
    return image_data;
}
