#include "core/image.h" // IWYU pragma: keep
#include "core/condition.h"
#include "core/logger.h"
#include "core/math.h"
#include <cstddef>
#include <vector>
#if defined(RAYGAME_BACKEND_RAYLIB)
#    include <raylib.h>
#endif

#if defined(RAYGAME_BACKEND_RAYLIB)
core::Image::Image(std::string_view filepath)
    : Image(static_cast<std::string>(filepath)) {}

core::Image::Image(const std::string& filepath)
    : _n_mipmaps(0) {
    core::log::debug(std::format("Creating Image from {}", filepath));
    ::Image rlImage = ::LoadImage(filepath.c_str());
    condition::check_condition(::IsImageReady(rlImage), "Image not ready");
    ::ImageMipmaps(&rlImage);
    ::ImageFormat(&rlImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    _width  = static_cast<int32_t>(rlImage.width);
    _height = static_cast<int32_t>(rlImage.height);
    _image_data.reserve(size_t(rlImage.width) * rlImage.height * sizeof(Pixel));
    const auto image_size = math::numeric_cast<size_t>(_width * _height);
    _image_data = *static_cast<std::vector<Pixel>*>(rlImage.data);
}

#elif defined(RAYGAME_BACKEND_SDL)
#endif
