#pragma once
#include <filesystem>
#include <vector>

namespace resmk {

void resmk(
    const std::filesystem::path&              header,
    const std::vector<std::filesystem::path>& resfiles,
    const std::string&                        outer_namespace,
    const std::string&                        ns_name
);

} // namespace resmk
