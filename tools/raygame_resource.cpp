#include <filesystem>
#include <print>
#include <string>
#include <vector>

namespace {

constexpr std::string progname{"ray_resource"};

int print_help() {
    std::println("{}: Creates a RayGame resource from a file", progname);
    std::println("Usage: {} [options] <header> <files...>", progname);
    std::println("      -h|--help       Displays this message");
    return 0;
}

enum class ResType : uint8_t {
    UNKNOWN,
    PNG,
};

ResType get_restype(const std::filesystem::path& source) {
    const std::string ext = source.extension().string();
    std::println("{}", ext);
    if (ext == ".png") {
        return ResType::PNG;
    }
    return ResType::UNKNOWN;
}

class Resource {
    std::string          m_name;
    std::vector<uint8_t> m_data;
    ResType              m_type;

public:
    explicit Resource(const std::filesystem::path& source)
        : m_name(source.stem().string())
        , m_type(get_restype(source)) {
    }
};

} // namespace

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
}
