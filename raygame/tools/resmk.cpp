#include "raygame/core/exception.h"
#include "raygame/core/io/file.h"
#include "raygame/core/logger.h"
#include <cstdint>
#include <filesystem>
#include <print>
#include <stb_image.h>
#include <string>
#include <vector>

namespace {
using core::log::debug;

class FileError: public core::exception::Exception {
public:
    FileError(const FileError&)            = default;
    FileError(FileError&&)                 = delete;
    FileError& operator=(const FileError&) = default;
    FileError& operator=(FileError&&)      = delete;

    explicit FileError(const std ::string& message)
        : core::exception::Exception(message) {}

    explicit FileError(const core::exception::Exception&& error)
        : core::exception::Exception(error) {}

    ~FileError() noexcept override = default;
};

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

    [[nodiscard]]
    constexpr std::string to_string(ResType enum_item) const {
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

    [[nodiscard]]
    std::string str() const {
        return m_source.string();
    }

    void process_png() {
        constexpr size_t N_CH = 4;
        int              height{0};
        int              width{0};
        int              channels{0};
        core::io::File   pngfile{m_source, "rb"};
        if (!pngfile.good()) {
            throw FileError(std::format("Bad file"));
        }
        debug("pngfile: {}", pngfile.fname());
        uint8_t* const data = stbi_load_from_file(pngfile.raw(), &width, &height, &channels, N_CH);
        m_out_type          = std::format("core::drawing::Image<{}, {}>", width, height);
        for (int yval{0}; yval < height; ++yval) {
            m_data.emplace_back("\n    ");
            const size_t row_off = (N_CH * width * yval);
            for (int xval{0}; xval < width; xval++) {
                const size_t  col_off = (N_CH * static_cast<size_t>(xval));
                // NOLINTBEGIN(*-pointer-arithmetic)
                const uint8_t r_val   = data[row_off + col_off + 0U];
                const uint8_t g_val   = data[row_off + col_off + 1U];
                const uint8_t b_val   = data[row_off + col_off + 2U];
                const uint8_t a_val   = data[row_off + col_off + 3U];
                // NOLINTEND(*-pointer-arithmetic)
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

    [[nodiscard]]
    const std::string& name() const {
        return m_name;
    }

    [[nodiscard]]
    std::string declaration() const {
        return std::format("extern const {} {};", m_out_type, m_name);
    }

    [[nodiscard]]
    std::string definition() const {
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

struct Config {
    bool                  header_set{false};
    std::filesystem::path header;
    std::vector<Resource> resources;
    std::string           outer_namespace;
    std::string           ns_name;
};

// NOLINTNEXTLINE(*-c-arrays)
Config handle_args(const int argc, char* const argv[]) {
    Config config;
    for (int argn{1}; argn < argc; argn++) {
        const std::string arg{argv[argn]}; //NOLINT(*-pointer-arithmetic)
        if (arg.starts_with('-')) {
            if (arg == "-h" || arg == "--help") {
                print_help();
            }
            if (arg == "-n" || arg == "--namespace") {
                config.outer_namespace = argv[++argn]; //NOLINT(*-pointer-arithmetic)
            }
        } else {
            if (!config.header_set) {
                config.header_set = true;
                config.header     = arg;
            } else {
                config.resources.emplace_back(arg);
            }
        }
    }
    config.ns_name = config.header.stem().string();
    for (auto& resource: config.resources) {
        resource.process();
    }
    return config;
}
} // namespace

// NOLINTNEXTLINE(*-exception-escape)
int main(int argc, char* argv[]) {
    const Config config = handle_args(argc, argv);
    if (config.header.string().empty()) {
        return 1;
    }
    core::io::File hdrfile{config.header, core::io::File::mode::write};
    hdrfile.writeln("#include \"raygame/core/drawing/image.h\"");
    if (!config.outer_namespace.empty()) {
        hdrfile.writeln(std::format("namespace {} {{", config.outer_namespace));
    }
    hdrfile.writeln(std::format("namespace {} {{", config.ns_name));
    for (const auto& resource: config.resources) {
        hdrfile.writeln(resource.declaration());
        std::string fname         = hdrfile.fname();
        fname[fname.length() - 1] = 'c';
        fname.append("pp");
        core::io::File srcfile{fname, "w"};
        srcfile.writeln("#include \"raygame/core/drawing/image.h\"");
        srcfile.writeln("using core::colour::rgba;");
        if (!config.outer_namespace.empty()) {
            srcfile.writeln(std::format("namespace {} {{", config.outer_namespace));
        }
        srcfile.writeln(std::format("namespace {} {{", config.ns_name));
        srcfile.writeln(resource.definition());
        srcfile.writeln("}");
        if (!config.outer_namespace.empty()) {
            srcfile.writeln("}");
        }
    }
    hdrfile.writeln("}");
    if (!config.outer_namespace.empty()) {
        hdrfile.writeln("}");
    }
}
