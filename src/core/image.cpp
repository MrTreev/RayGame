#include "core/image.h" // IWYU pragma: keep
#include "core/gui/backend.h"
#include <vector>

core::Image::Image(std::string_view filepath)
    : Image(static_cast<std::string>(filepath.data())) {}

core::Image::Image(const std::string& filepath)
    : _n_mipmaps(0) {
    ::Image rlImage = ::LoadImage(filepath.c_str());
    ::ImageFormat(&rlImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    int rlImageSize = static_cast<int>(rlImage.width * rlImage.height)
                      * static_cast<int>(sizeof(Pixel));
    _width  = static_cast<int_t>(rlImage.width);
    _height = static_cast<int_t>(rlImage.height);
    const unsigned char* rlData =
        ::ExportImageToMemory(rlImage, ".png", &rlImageSize);
    _image_data = std::vector<core::Pixel>(
        rlData,
        rlData + static_cast<const int_t>(rlImageSize) // NOLINT
    );
}
