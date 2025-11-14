#include "raygame/tools/resmk/resources/png.h"
#include "raygame/core/io/file.h"
#include "raygame/core/logger.h"
#include "raygame/core/math/numeric_cast.h"
#include <stb_image.h>

void PngFile::process_impl() {
    core::io::File pngfile{m_source, "rb"};
    if (!pngfile.good()) {
        throw FileError(std::format("Bad file"));
    }
    core::log::debug("pngfile: {}", pngfile.fname());
    m_data = stbi_load_from_file(pngfile.raw(), &m_width, &m_height, &m_channels, N_CH);
}

void PngFile::content(std::string& stuff) const {
    stuff += std::format("    std::array<core::Pixel, {}>{{", (m_width * m_height));
    for (int yval{0}; yval < m_height; ++yval) {
        stuff += "\n        ";
        const size_t row_off =
            (N_CH * core::math::numeric_cast<size_t>(m_width)
             * core::math::numeric_cast<size_t>(yval));
        for (int xval{0}; xval < m_width; xval++) {
            const size_t  col_off  = (N_CH * static_cast<size_t>(xval));
            // NOLINTBEGIN(*-pointer-arithmetic)
            const uint8_t r_val    = m_data[row_off + col_off + 0U];
            const uint8_t g_val    = m_data[row_off + col_off + 1U];
            const uint8_t b_val    = m_data[row_off + col_off + 2U];
            const uint8_t a_val    = m_data[row_off + col_off + 3U];
            // NOLINTEND(*-pointer-arithmetic)
            stuff                 += std::format(
                "core::colour::rgba({:#04x},{:#04x},{:#04x},{:#04x}), ",
                r_val,
                g_val,
                b_val,
                a_val
            );
        }
    }
    stuff += "\n    }";
}

[[nodiscard]]
std::string PngFile::type() const {
    return std::format("core::drawing::Image<{}, {}>", m_width, m_height);
}
