#include "raygame/core/condition.h"
#include "raygame/core/exception.h"
#include "raygame/core/io/file.h"
#include "raygame/core/logger.h"
#include <cstdint>
#include <filesystem>
#include <png.h>
#include <print>
#include <string>
#include <vector>

namespace {
using core::log::debug;
using core::log::trace;

constexpr std::string progname{"ray_resource"};

int print_help() {
    std::println("{}: Creates a RayGame resource from a file", progname);
    std::println("Usage: {} [options] <header> <files...>", progname);
    std::println("      -h|--help       Displays this message");
    return 0;
}

struct png_ptrdel {
    void operator()(png_struct* ptr) { png_destroy_read_struct(&ptr, nullptr, nullptr); }

    void operator()(png_info* ptr) { png_destroy_read_struct(nullptr, &ptr, nullptr); }
};

std::string col_to_string(int color_type) {
    switch (color_type) {
    case PNG_COLOR_TYPE_GRAY:       return "PNG_COLOR_TYPE_GRAY";
    case PNG_COLOR_TYPE_GRAY_ALPHA: return "PNG_COLOR_TYPE_GRAY_ALPHA";
    case PNG_COLOR_TYPE_PALETTE:    return "PNG_COLOR_TYPE_PALETTE";
    case PNG_COLOR_TYPE_RGB:        return "PNG_COLOR_TYPE_RGB";
    case PNG_COLOR_TYPE_RGB_ALPHA:  return "PNG_COLOR_TYPE_RGB_ALPHA";
    default:                        return "INVALID COLOR TYPE";
    }
}

std::string interlace_to_string(int interlace_type) {
    switch (interlace_type) {
    case PNG_INTERLACE_NONE:  return "none";
    case PNG_INTERLACE_ADAM7: return "ADAM7";
    default:                  return "INVALID INTERLACE TYPE";
    }
}

std::string channels_to_string(int channels) {
    switch (channels) {
    case 1:  return std::format("{} (GRAY, PALETTE)", channels);
    case 2:  return std::format("{} (GRAY_ALPHA)", channels);
    case 3:  return std::format("{} (RGB)", channels);
    case 4:  return std::format("{} (RGB_ALPHA or RGBF)", channels);
    default: return "INVALID NUMBER OF CHANNELS";
    }
}

class Resource {
    enum class ResType : uint8_t {
        UNKNOWN,
        PNG,
    };

    constexpr std::string to_string(ResType enum_item) {
        switch (enum_item) {
        case ResType::UNKNOWN: return "UNKNOWN";
        case ResType::PNG:     return "PNG";
        }
    }

    std::filesystem::path    m_source;
    std::string              m_name;
    std::string              m_out_type;
    std::vector<std::string> m_data;
    ResType                  m_type;

    std::string str() { return m_source.string(); }

    template<typename T>
    using png_ptr_t = std::unique_ptr<T, png_ptrdel>;

    void process_png() {
        constexpr size_t PNG_HEADER_LEN{8};
        using png_hdr_t = std::array<u_char, PNG_HEADER_LEN>;
        core::io::File pngfile{m_source, "rb"};
        png_hdr_t      header{0};
        if (std::fread(header.data(), 1, header.size(), pngfile.raw()) != header.size()) {
            throw std::system_error(errno, std::system_category());
        }
        trace("{} is valid file", str());
        core::condition::check_condition(
            (png_sig_cmp(header.data(), 0, header.size()) == 0),
            std::format("ERROR: '{}' is not a PNG file", str())
        );
        trace("{} is valid PNG", str());
        const png_ptr_t<png_struct> png_ptr{
            png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr)
        };
        core::condition::check_condition(
            png_ptr,
            std::format("Could not allocate png_struct for: {}", str())
        );
        trace("{} struct allocated", str());
        const png_ptr_t<png_info> info_ptr{png_create_info_struct(png_ptr.get())};
        png_init_io(png_ptr.get(), pngfile.raw());
        png_set_sig_bytes(png_ptr.get(), static_cast<int>(PNG_HEADER_LEN));
        png_read_info(png_ptr.get(), info_ptr.get());
        const size_t width          = png_get_image_width(png_ptr.get(), info_ptr.get());
        const size_t height         = png_get_image_height(png_ptr.get(), info_ptr.get());
        const int    bit_depth      = png_get_bit_depth(png_ptr.get(), info_ptr.get());
        const int    color_type     = png_get_color_type(png_ptr.get(), info_ptr.get());
        const int    interlace_type = png_get_interlace_type(png_ptr.get(), info_ptr.get());
        const int    channels       = png_get_channels(png_ptr.get(), info_ptr.get());
        const size_t rowbytes       = png_get_rowbytes(png_ptr.get(), info_ptr.get());
        debug("{} data:", str());
        debug("    size:            {}x{}", width, height);
        debug("    bit_depth:       {}", bit_depth);
        debug("    color_type:      {}", col_to_string(color_type));
        debug("    interlace_type:  {}", interlace_to_string(interlace_type));
        debug("    channels:        {}", channels_to_string(channels));
        debug("    rowbytes:        {}", rowbytes);
        debug("    bytesize:        {}", sizeof(png_byte));
        m_out_type = std::format("core::drawing::Image<{}, {}>", width, height);
        std::vector<png_byte*> row_ptr{};
        row_ptr.reserve(height);
        for (size_t row_n = 0; row_n < height; ++row_n) {
            // NOLINTNEXTLINE
            row_ptr[row_n] = reinterpret_cast<png_byte*>(malloc(rowbytes));
        }
        // read image data
        png_read_image(png_ptr.get(), row_ptr.data());
        for (size_t yval{0}; yval < height; ++yval) {
            m_data.emplace_back("\n    ");
            for (size_t xval{0}; xval < width; xval++) {
                auto get_next = [bit_depth, &row_ptr, xval, yval]() {
                    constexpr uint64_t bits   = sizeof(png_byte) * 8;
                    const uint64_t     depth  = bit_depth / bits;
                    const uint64_t     byte_0 = row_ptr[yval][((sizeof(png_byte) / 2) * xval) + 0];
                    const uint64_t     byte_1 = row_ptr[yval][((sizeof(png_byte) / 2) * xval) + 1];
                    const uint64_t     byte_2 = row_ptr[yval][((sizeof(png_byte) / 2) * xval) + 2];
                    const uint64_t     byte_3 = row_ptr[yval][((sizeof(png_byte) / 2) * xval) + 3];
                    switch (depth) {
                        // clang-format off
                        // NOLINTBEGIN
                    case 1: return (byte_0 << (0 * bits));
                    case 2: return (byte_0 << (1 * bits)) + (byte_1 << (0 * bits));
                    case 3: return (byte_0 << (2 * bits)) + (byte_1 << (1 * bits)) + (byte_2 << (0 * bits));
                    case 4: return (byte_0 << (3 * bits)) + (byte_1 << (2 * bits)) + (byte_2 << (1 * bits)) + (byte_3 << (0 * bits));
                        // NOLINTEND
                        // clang-format on
                    default: core::condition::unknown(std::format("depth: {}", depth));
                    }
                };
                const uint64_t data_r = get_next();
                const uint64_t data_g = get_next();
                const uint64_t data_b = get_next();
                const uint64_t data_a = get_next();
                const uint8_t  r_val  = data_r;
                const uint8_t  g_val  = data_g;
                const uint8_t  b_val  = data_b;
                const uint8_t  a_val  = data_a;
                m_data.push_back(
                    std::format(
                        "rgba({:#04x},{:#04x},{:#04x},{:#04x}), ",
                        r_val,
                        g_val,
                        b_val,
                        a_val
                    )
                );
            }
        }
        for (auto& row: row_ptr) {
            // NOLINTNEXTLINE
            free(row);
            row = nullptr;
        }
        debug("allocated");
    }

public:
    explicit Resource(std::filesystem::path source)
        : m_source(std::move(source))
        , m_name(m_source.stem().string())
        , m_type([](const std::string& ext) {
            //NOLINTBEGIN(*-braces-around-statements)
            if (ext == ".png") return ResType::PNG;
            //NOLINTEND(*-braces-around-statements)
            return ResType::UNKNOWN;
        }(m_source.extension().string())) {}

    const std::string& name() { return m_name; }

    std::string declaration() { return std::format("extern const {} {};", m_out_type, m_name); }

    std::string definition() {
        std::string definition{};
        definition += std::format("const {} {} = {{", m_out_type, m_name);
        for (size_t idx{0}; idx < m_data.size(); ++idx) {
            definition += m_data[idx];
        }
        definition += std::format("}};");
        return definition;
    }

    void process() {
        debug("Processing: {}", m_name);
        debug("    Type: {}", to_string(m_type));
        switch (m_type) {
        case ResType::PNG: process_png(); break;
        case ResType::UNKNOWN:
            throw core::exception::Unimplemented(
                std::format("Unknown file extension: {}", m_source.extension().string())
            );
        }
    }
};

} // namespace

// NOLINTNEXTLINE(*-exception-escape)
int main(int argc, char* argv[]) {
    bool                  header_set{false};
    std::filesystem::path header{};
    std::vector<Resource> resources;
    for (int argn{1}; argn < argc; ++argn) {
        const std::string arg{argv[argn]}; //NOLINT(*-pointer-arithmetic)
        if (arg.starts_with('-')) {
            if (arg == "-h" || arg == "--help") {
                print_help();
            }
        } else {
            if (!header_set) {
                header_set = true;
                header     = arg;
            } else {
                resources.emplace_back(arg);
            }
        }
    }
    for (auto& resource: resources) {
        resource.process();
    }
    for (auto& resource: resources) {
        debug("Resource declaration:");
        debug("{}", resource.declaration());
        debug("Resource definition:");
        debug("{}", resource.definition());
    }
}
