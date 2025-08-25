#include <filesystem>
#include <print>
#include <string>

int main(int argc, char* argv[]) {
    //NOLINTNEXTLINE(*-pointer-arithmetic)
    const std::string progname{argv[0]};
    std::println("{}", progname);
    std::filesystem::path header{};
    for (int argn{1}; argn < argc; ++argn) {
        //NOLINTNEXTLINE(*-pointer-arithmetic)
        const std::string arg{argv[argn]};
        std::println("Parsing argument: {}", arg);
        if (arg.starts_with('-')) {
            if (arg == "-h" || arg == "--help") {
                std::println("{}: Creates a RayGame resource from a file", progname);
                std::println("Usage: {} [options] <header> <files...>", progname);
                std::println("      -h|--help       Displays this message");
            }
        }
    }
}
