#include "raygame/core/logger.hpp"
#include "raygame/tools/resmk/resources/png.hpp"
#include "raygame/tools/resmk/resources/resmk.hpp"
#include "raygame/tools/resmk/resources/resource.hpp"
#include <algorithm>
#include <filesystem>
#include <memory>
#include <print>
#include <string>
#include <vector>

namespace {

constexpr std::string progname{"resmk"};
using resmk::PngFile;
using resmk::Resource;

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

class Help: public core::exception::Exception {
public:
    Help(const Help&)            = default;
    Help(Help&&)                 = delete;
    Help& operator=(const Help&) = default;
    Help& operator=(Help&&)      = delete;

    explicit Help()
        : core::exception::Exception("") {}

    ~Help() noexcept override = default;
};

struct Config {
    bool                                   m_header_set{false};
    std::filesystem::path                  m_header;
    std::vector<std::unique_ptr<Resource>> m_resources;
    std::string                            m_outer_namespace;
    std::string                            m_ns_name;
};

// NOLINTNEXTLINE(*-c-arrays)
Config handle_args(const int argc, const char* const argv[]) {
    Config config;
    for (int argn{1}; argn < argc; argn++) {
        const std::string arg{argv[argn]}; //NOLINT(*-pointer-arithmetic)
        if (arg.starts_with('-')) {
            if (arg == "-h" || arg == "--help") {
                throw Help();
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

int main(int argc, char* argv[]) {
    try {
        const Config config = handle_args(argc, argv);
        if (config.m_header.string().empty()) {
            throw std::runtime_error("Empty header string");
        }
        if (config.m_resources.empty()) {
            throw std::runtime_error("No resources given");
        }
        resmk::resmk(
            config.m_header,
            config.m_resources,
            config.m_outer_namespace,
            config.m_ns_name
        );
    } catch (const Help&) {
        print_help();
        return 0;
    } catch (const std::runtime_error& err) {
        core::log::error("ERROR: {}", err.what());
        return 1;
    } catch (...) {
        core::log::error("ERROR: Unknown Error");
        return 1;
    }
}
