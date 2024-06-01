#include "core/image.h" // IWYU pragma: keep
#include "core/gui/backend.h"
#include <cstddef>
#include <vector>

core::Image::Image(std::string_view filepath)
    : Image(static_cast<std::string>(filepath.data())) {}

core::Image::Image(const std::string& filepath) {
    ::Image rlImage = ::LoadImage(filepath.c_str());
    ::ImageFormat(&rlImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    int rlImageSize = static_cast<int>(rlImage.width * rlImage.height)
                      * static_cast<int>(sizeof(Pixel));
    _width  = static_cast<size_t>(rlImage.width);
    _height = static_cast<size_t>(rlImage.height);
    const unsigned char* rlData =
        ::ExportImageToMemory(rlImage, ".png", &rlImageSize);
    _image_data = std::vector<core::Pixel>(
        rlData,
        rlData + static_cast<const size_t>(rlImageSize) // NOLINT
    );
}
