#include "raygame/core/condition.h"
#include "raygame/core/config.h"
#include "raygame/core/exception.h"
#include "raygame/core/io/file.h"
#include "raygame/core/logger.h"
#include "raygame/core/math/numeric_cast.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <memory>
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
    virtual void process_impl() {
        throw core::exception::Unimplemented(
            std::format("Unknown file extension: {}", m_source.extension().string())
        );
    }

    [[nodiscard]]
    virtual std::string type() const {
        core::condition::unimplemented();
    }

    virtual void content([[maybe_unused]] std::string& stuff) const {
        core::condition::unimplemented();
    }

public:
    std::filesystem::path m_source; // NOLINT
    std::string           m_name;   // NOLINT

    RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
    RAYGAME_CLANG_SUPPRESS_WARNING("-Wunused-member-function")
    virtual ~Resource()                  = default;
    Resource(const Resource&)            = default;
    Resource(Resource&&)                 = default;
    Resource& operator=(const Resource&) = default;
    Resource& operator=(Resource&&)      = default;
    RAYGAME_CLANG_SUPPRESS_WARNING_POP

    explicit Resource(std::filesystem::path source)
        : m_source(std::move(source))
        , m_name(m_source.stem().string()) {}

    [[nodiscard]]
    std::string declaration() const {
        return std::format("extern const {} {};", type(), m_name);
    }

    [[nodiscard]]
    std::string definition(std::string prefix) const {
        std::string definition{};
        definition += "RAYGAME_CLANG_SUPPRESS_WARNING_PUSH\n";
        definition += "RAYGAME_CLANG_SUPPRESS_WARNING(\"-Wglobal-constructors\")\n";
        definition += "// NOLINTNEXTLINE(cert-err58-cpp)\n";
        definition += std::format("const {} {}{} {{\n", type(), prefix, m_name);
        content(definition);
        definition += std::format("\n}};\n");
        definition += "RAYGAME_CLANG_SUPPRESS_WARNING_POP\n";
        return definition;
    }

    void process() {
        debug("Processing: {}", m_name);
        process_impl();
    }
};

class PngFile: public Resource {
    int      m_width{0};
    int      m_height{0};
    int      m_channels{0};
    uint8_t* m_data{nullptr};

    static constexpr size_t N_CH = 4;

    void process_impl() override {
        core::io::File pngfile{m_source, "rb"};
        if (!pngfile.good()) {
            throw FileError(std::format("Bad file"));
        }
        debug("pngfile: {}", pngfile.fname());
        m_data = stbi_load_from_file(pngfile.raw(), &m_width, &m_height, &m_channels, N_CH);
    }

    void content(std::string& stuff) const override {
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
    std::string type() const override {
        return std::format("core::drawing::Image<{}, {}>", m_width, m_height);
    }

public:
    explicit PngFile(std::filesystem::path source)
        : Resource(std::move(source)) {}
};

std::unique_ptr<Resource> make_resource(std::filesystem::path source) {
    std::string ext = source.extension().string();
    std::ranges::transform(ext, ext.begin(), [](char cha) {
        if (cha >= 'A' && cha <= 'Z') {
            constexpr char TO_LOW{32};
            return static_cast<char>(cha + TO_LOW);
        }
        return cha;
    });
    if (ext == ".png") {
        return std::make_unique<PngFile>(std::move(source));
    }
    return std::make_unique<Resource>(std::move(source));
}

struct Config {
    bool                                   header_set{false};
    std::filesystem::path                  header;
    std::vector<std::unique_ptr<Resource>> resources;
    std::string                            outer_namespace;
    std::string                            ns_name;
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
                config.resources.push_back(make_resource(arg));
            }
        }
    }
    config.ns_name = config.header.stem().string();
    for (auto& resource: config.resources) {
        resource->process();
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
    hdrfile.writeln("");
    if (!config.outer_namespace.empty()) {
        hdrfile.writeln(std::format("namespace {} {{", config.outer_namespace));
    }
    hdrfile.writeln(std::format("namespace {} {{", config.ns_name));
    for (const auto& resource: config.resources) {
        hdrfile.writeln(resource->declaration());
        std::string fname         = hdrfile.fname();
        fname[fname.length() - 1] = 'c';
        fname.append("pp");
        core::io::File srcfile{fname, "w"};
        srcfile.writeln("#include \"raygame/core/drawing/image.h\"");
        srcfile.writeln(std::format("#include \"{}\"", config.header.string()));
        srcfile.writeln(resource->definition(config.ns_name + "::"));
    }
    hdrfile.writeln(std::format("}} // namespace {}", config.ns_name));
    if (!config.outer_namespace.empty()) {
        hdrfile.writeln(std::format("}} // namespace {}", config.outer_namespace));
    }
}
