#include <print>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    //NOLINTNEXTLINE(*-pointer-arithmetic)
    const std::string progname{argv[0]};
    std::println("{}", progname);
    //NOLINTNEXTLINE(*-avoid-c-arrays)
    const std::vector<std::string> args{[argc, argv]() {
        std::vector<std::string> args{};
        for (int argn{1}; argn < argc; ++argn) {
            //NOLINTNEXTLINE(*-pointer-arithmetic)
            args.emplace_back(argv[argn]);
        }
        return args;
    }()};
    for (const auto& arg: args) {
        if (arg == "-h" || arg == "--help") {
            std::println("{}: Creates a RayGame resource from a file", progname);
        }
        std::println("{}", arg);
    }
}
