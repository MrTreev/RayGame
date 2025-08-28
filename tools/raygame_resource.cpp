#include "raygame/core/condition.h"
#include "raygame/core/exception.h"
#include "raygame/core/io/file.h"
#include "raygame/core/logger.h"
#include <filesystem>
#include <png.h>
#include <print>
#include <string>
#include <vector>

namespace {
using core::log::debug;

constexpr std::string progname{"ray_resource"};

int print_help() {
    std::println("{}: Creates a RayGame resource from a file", progname);
    std::println("Usage: {} [options] <header> <files...>", progname);
    std::println("      -h|--help       Displays this message");
    return 0;
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

    std::filesystem::path m_source;
    std::string           m_name;
    std::string           m_out_type;
    std::vector<uint8_t>  m_data;
    ResType               m_type;

    std::string str() { return m_source.string(); }

    void process_png() {
        constexpr size_t PNG_HEADER_LEN{8};
        using png_hdr = std::array<u_char, PNG_HEADER_LEN>;
        core::io::File pngfile{m_source, "rb"};
        png_hdr        header{0};
        if (std::fread(header.data(), 1, header.size(), pngfile.raw()) != header.size()) {
            throw std::system_error(errno, std::system_category());
        }
        debug("{} is valid file", str());
        core::condition::check_condition(
            (png_sig_cmp(header.data(), 0, header.size()) == 0),
            std::format("ERROR: '{}' is not a PNG file", str())
        );
        debug("{} is valid PNG", str());
        png_struct* png_ptr =
            png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        core::condition::check_ptr(
            png_ptr,
            std::format("Could not allocate png_struct for: {}", str())
        );
        const size_t img_width{};
        const size_t img_height{};
        m_out_type = std::format("core::drawing::Image<{}, {}>", img_width, img_height);
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

    std::string declaration() { return std::format("extern const {} {};", m_out_type, m_name); }

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
}
