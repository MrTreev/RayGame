#include "core/image.h" // IWYU pragma: keep
#include "core/config.h"
#include "core/logger.h"
#include <vector>

#if defined(RAYGAME_BACKEND_RAYLIB)
core::Image::Image(std::string_view filepath)
    : Image(static_cast<std::string>(filepath)) {}

core::Image::Image(const std::string& filepath)
    : _n_mipmaps(0) {
    ::Image rlImage = ::LoadImage(filepath.c_str());
    ::ImageMipmaps(&rlImage);
    core::log::debug("image created");
    ::ImageFormat(&rlImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    core::log::debug("image formatted");
    int rlImageSize = static_cast<int>(rlImage.width * rlImage.height)
                      * static_cast<int>(sizeof(Pixel));
    _width  = static_cast<int_t>(rlImage.width);
    _height = static_cast<int_t>(rlImage.height);
    core::log::debug("data set");
    const unsigned char* rlData =
        ::ExportImageToMemory(rlImage, ".png", &rlImageSize);
    core::log::debug("exported to memory");
    _image_data = std::vector<core::Pixel>(
        rlData,
        rlData + static_cast<const int_t>(rlImageSize) // NOLINT
    );
    core::log::debug("vector created");
}
#endif

core::Image::~Image() {
    core::log::debug("destructor");
};
