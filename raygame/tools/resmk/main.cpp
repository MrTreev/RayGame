#include "raygame/core/io/file.h"
#include "raygame/tools/resmk/resources/png.h"
#include "raygame/tools/resmk/resources/resource.h"
#include <algorithm>
#include <filesystem>
#include <memory>
#include <print>
#include <string>
#include <vector>

namespace {

constexpr std::string progname{"resmk"};

int print_help() {
    std::println("{}: Creates a RayGame resource from a file", progname);
    std::println("Usage: {} [options] <header> <files...>", progname);
    std::println("    -h|--help                  Displays this message");
    std::println("    -n|--namespace <namespace> Sets the outer namespace");
    return 0;
}

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
    bool                                   m_header_set{false};
    std::filesystem::path                  m_header;
    std::vector<std::unique_ptr<Resource>> m_resources;
    std::string                            m_outer_namespace;
    std::string                            m_ns_name;
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
                config.m_outer_namespace = argv[++argn]; //NOLINT(*-pointer-arithmetic)
            }
        } else {
            if (!config.m_header_set) {
                config.m_header_set = true;
                config.m_header     = arg;
            } else {
                config.m_resources.push_back(make_resource(arg));
            }
        }
    }
    config.m_ns_name = config.m_header.stem().string();
    for (auto& resource: config.m_resources) {
        resource->process();
    }
    return config;
}
} // namespace

// NOLINTNEXTLINE(*-exception-escape)
int main(int argc, char* argv[]) {
    const Config config = handle_args(argc, argv);
    if (config.m_header.string().empty()) {
        return 1;
    }
    core::io::File hdrfile{config.m_header, core::io::File::mode::write};
    hdrfile.gencode("#include \"raygame/core/drawing/image.h\"");
    hdrfile.writeln("");
    if (!config.m_outer_namespace.empty()) {
        hdrfile.gencode(std::format("namespace {} {{", config.m_outer_namespace));
    }
    hdrfile.gencode(std::format("namespace {} {{", config.m_ns_name));
    for (const auto& resource: config.m_resources) {
        hdrfile.gencode(resource->declaration());
        std::string fname         = hdrfile.fname();
        fname[fname.length() - 1] = 'c';
        fname.append("pp");
        core::io::File srcfile{fname, "w"};
        srcfile.gencode("#include \"raygame/core/drawing/image.h\"");
        srcfile.gencode(std::format("#include \"{}\"", config.m_header.string()));
        srcfile.gencode(resource->definition(config.m_ns_name + "::"));
    }
    hdrfile.gencode(std::format("}} // namespace {}", config.m_ns_name));
    if (!config.m_outer_namespace.empty()) {
        hdrfile.gencode(std::format("}} // namespace {}", config.m_outer_namespace));
    }
}
